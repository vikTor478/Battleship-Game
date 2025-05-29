#include "PlayerTurnState.h"
#include "EnemyTurnState.h"
#include "WinState.h"
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
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard(), game.getShipCount());
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
    std::cout << "Your turn. Enter coordinates (e.g., B4): ";
   
    while (true) 
    {
        std::cin >> input;
        inputPair = InputParseHandler::parseCoordinates(input);

        if (inputPair.first != -1 && inputPair.second != -1) 
        {
            CellState cell = game.getOpponentBoard()->getCellState(inputPair.first, inputPair.second);
            if (cell == Hit || cell == Miss) 
            {
                std::cout << "You've already targeted that cell. Try again: ";
                continue;
            }
            break;
        }

        std::cout << "Invalid input. Try Again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    game.incrementPlayerTurn();
    
    game.getOpponentBoard() -> markHit(inputPair.first, inputPair.second);

    if(game.getOpponentBoard()->allShipsSunk()){
        game.incrementPlayerHit();
        game.changeState(new WinState());
        return;
    }

    CellState targetCellState = game.getOpponentBoard() -> getCellState(inputPair.first, inputPair.second);

    if(targetCellState == Hit)
    {
        game.incrementPlayerHit();
    }
    else
    {
       game.incrementPlayerMiss();
    }

    game.changeState(new EnemyTurnState());
}

void PlayerTurnState::exit(Game& game)
{
    std::cout << "=== Player turn ended ===\n";
}