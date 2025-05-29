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
    isExtraTurn = false;

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
   
    if(!isExtraTurn){
            std::cout<<"Your turn. Enter coordinates (e.g., B4): ";
    }

    while (true) 
    {
        std::cin >> input;
        inputPair = InputParseHandler::parseCoordinates(input);

        if (inputPair.first != -1 && inputPair.second != -1) 
        {
            if(game.getOpponentBoard()->wasAlreadyShot(inputPair.first, inputPair.second)){
                std::cout<<"You already targeted that cell. Try again: ";
                continue;
            }
            break;
        }

        std::cout << "Invalid input. Try Again: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    game.incrementPlayerTurn();
    
    bool hit = game.getOpponentBoard() -> markHit(inputPair.first, inputPair.second);

    if(hit){
        game.incrementPlayerHit();
    }
    else{
        game.incrementPlayerMiss();
    }

    if(game.getOpponentBoard()->allShipsSunk()){
        game.incrementPlayerHit();
        game.incrementPlayerTurn();
        game.changeState(new WinState());
        return;
    }
    
    CellState targetCellState = game.getOpponentBoard() -> getCellState(inputPair.first, inputPair.second);

    if(targetCellState == Hit)
    {
        game.changeState(new PlayerTurnState());
    }
    else
    {
       game.changeState(new EnemyTurnState());
    }
}

void PlayerTurnState::exit(Game& game)
{
    std::cout << "=== Player turn ended ===\n";
}