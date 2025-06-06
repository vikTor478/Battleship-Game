#include "PlayerTurnState.h"
#include "MainMenuState.h"
#include "EnemyTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include "InputParseHandler.h"
#include <utility>
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>

using namespace States;

namespace States
{
    void PlayerTurnState::enter(Game& game)
    {
        isExtraTurn = false;

        if (game.getPlayerBoard() && game.getOpponentBoard()) 
        {
            Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard(), game.getShipCount(), game.getBoardSize());
            std::cout << "\n\n=== Player turn started ===\n";
        } 
        else
        {
            std::cerr << "Error: boards are bot initialized\n";
        }
    }

    void PlayerTurnState::update(Game& game)
    {
        std::cout<<"Your turn. Enter coordinates: ";
        std::string input;
        std::pair<int,int> inputPair = { 0, 0 };

        while (true) 
        {
            std::cin >> input;

            inputPair = InputParseHandler::parseCoordinates(input, game.getBoardSize());

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

        ++game;
        
        game.getOpponentBoard() -> markHit(inputPair.first, inputPair.second, game);


        if(game.getOpponentBoard()->allShipsSunk()){
            game.incrementPlayerHit();
            ++game;
            Renderer::ShowEndScreen(true, game);
            game.changeState(new MainMenuState());
            return;
        }

        CellState targetCellState = game.getOpponentBoard() -> getCellState(inputPair.first, inputPair.second);

        if(targetCellState == Hit)
        {
            game.incrementPlayerHit();
            std::cout << "\nDirect hit! Fire again.\n";
            game.changeState(new PlayerTurnState());
        }
        else
        {
            game.incrementPlayerMiss();
            game.changeState(new EnemyTurnState());
        }
    }

    void PlayerTurnState::exit(Game& game)
    {
        if(!game.getOpponentBoard() -> allShipsSunk())
        {
            std::cout << "\n=== Player turn ended ===\n";
            system("pause");
        }
        else
        {
            game.fullRestart();
            game.quit();
        }
    }
}