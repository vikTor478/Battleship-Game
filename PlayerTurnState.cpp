#include "PlayerTurnState.h"
#include "EnemyTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include "InputParseHandler.h"
#include <utility>
#include <iostream>
#include <limits>

void PlayerTurnState::enter(Game& game)
{
    if (game.getPlayerBoard() && game.getOpponentBoard()) 
    {
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard());
        std::cout << "=== Player turn started ===\n";
    } 
    else 
    {
        std::cerr << "Error: boards are bot initialized\n";
    }
}

void PlayerTurnState::update(Game& game)
{
    std::string input;
    std::pair<int,int> inputPair = { 0, 0 };

    while (true) 
    {
        std::cout << "Your turn. Enter coordinates (e.g., B4): \n";
        std::cin >> input;
        inputPair = InputParseHandler::parseCoordinates(input);

        if (inputPair.first != -1 && inputPair.second != -1) 
        {
            break;
        }

        std::cout << "Invalid input. Try Again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    game.getOpponentBoard() -> markHit(inputPair.first, inputPair.second);

    CellState targetCellState = game.getOpponentBoard() -> getCellState(inputPair.first, inputPair.second);

    if(targetCellState == Hit)
    {
        game.changeState(new EnemyTurnState());
    }
    else
    {
       game.changeState(new PlayerTurnState());
    }

    game.changeState(new EnemyTurnState());
}

void PlayerTurnState::exit(Game& game)
{
    std::cout << "=== Player turn ended ===\n";
}