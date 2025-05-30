#include "Game.h"
#include "PlayerTurnState.h"
#include "MainMenuState.h"
#include "Board.h"
#include "Renderer.h"
#include <iostream>
#include <limits>

#include <cstdlib>
#include <ctime>

void MainMenuState::enter(Game& game)
{
    std::cout << "=========================================\n";
    std::cout << "        Welcome to Battleship Game!      \n";
    std::cout << "=========================================\n\n";
}

void MainMenuState::update(Game& game)
{
    int choice = 0;

    while (true) 
    {
        system("cls");
        std::cout << "\n=== Main Menu ===\n";
        std::cout << "1. Start Game\n";
        std::cout << "2. Settings\n";
        std::cout << "3. Rules\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
            system("pause");
            continue;
        }

        system("cls");

        switch (choice) 
        {
            case 1:
                game.changeState(new PlayerTurnState());
                return;

            case 2:
                showSettings(game);
                break;

            case 3:
                showRules();
                break;

            case 4:
                std::cout << "Exiting game. Goodbye!\n";
                std::exit(0);

            default:
                std::cout << "Invalid input. Please enter a number between 1 and 4.\n";
        }
    }
}

void showSettings(Game& game) 
{
    int choice = 0;

    while (true) 
    {
        system("cls");
        std::cout << "\n--- Settings ---\n";
        std::cout << "1. Select Difficulty\n";
        std::cout << "2. Set Grid Size\n";
        std::cout << "3. Select Game Mode\n";
        std::cout << "4. Main Menu\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        switch (choice) 
        {
            case 1:
                selectDifficulty(game);
                break;

            case 2:
                selectBoardSize(game);
                break;

            case 3:
                selectGameMode();
                break;

            case 4:
                return;

            default:
                std::cout << "Invalid input. Try again.\n";
        }
    }
}

void selectDifficulty(Game& game)
{
    int level;
    std::cout << "\nSelect difficulty:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
    std::cout << "Enter your choice: ";
    std::cin >> level;
    
    if (level >= 1 && level <= 3) 
    {
        game.setDifficultyLevel(static_cast<DifficultyLevel>(level - 1));
        std::cout << "\nDifficulty set successfully.\n";
    } 
    else 
    {
        std::cout << "\nInvalid choice. Please enter a number between 1 and 3.\n";
    }

    std::cout << "Press Enter to return...";
    std::cin.ignore(); std::cin.get();
}

void selectBoardSize(Game& game)
{
    int size;
    std::cout << "\n\nEnter prefered board size (min 5, max 26): \n";
    std::cin >> size;

    if (size >= 5 && size <= 26) 
    {
        game.setBoardSize(size);
        std::cout << "\nsize set successfully.\n";
    } 
    else 
    {
        std::cout << "\nInvalid choice. Please enter a number between 5 and 26.\n";
    }

    std::cout << "Press Enter to return...";
    std::cin.ignore(); std::cin.get();
}

void selectGameMode()
{
    
}

void showRules() 
{
    std::cout << "Here are the rules:\n";
    std::cout << "The game is played on a 10x10 grid.\n";
    std::cout << "You and the computer will each have your own grid.\n";
    std::cout << "Ships are placed randomly on the grid.\n";
    std::cout << "Take turns inputting coordinates to strike.\n";
    std::cout << "The Grid Symbols:\n";
    std::cout << "    '~' - Water (empty cell)\n";
    std::cout << "    'S' - Player's ship location\n";
    std::cout << "    'X' - Hit (a successful strike on a ship)\n";
    std::cout << "    '0' - Miss (a strike on water)\n";
    std::cout << "The first to sink all enemy ships wins!\n";
    std::cout << "Good Luck!\n\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore(); std::cin.get();
}


void MainMenuState::exit(Game& game)
{
    std::cout<< game.getBoardSize();
    int boardSize = game.getBoardSize();
    Board* playerBoard;
    Board* opponentBoard;
    
    if(boardSize > 5)
    {
        playerBoard = new Board(boardSize);
        opponentBoard = new Board(boardSize);
    }
    else
    {
        playerBoard = new Board();
        opponentBoard = new Board();
        game.setBoardSize(10);
    }

    game.setPlayerBoard(playerBoard);
    game.setOpponentBoard(opponentBoard);

    int shipCount = std::rand() % 4 + 1;
    game.setShipCount(shipCount);
    
    std::vector<int> shipLengths;
    for(int i=0; i<shipCount; ++i){
        int length = std::rand() % 4 + 2;
        shipLengths.push_back(length);
    }

    playerBoard->placeGameShips(shipLengths, game.getBoardSize());
    opponentBoard->placeGameShips(shipLengths, game.getBoardSize());
}