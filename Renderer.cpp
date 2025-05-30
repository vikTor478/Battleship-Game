#include "Renderer.h"
#include "Game.h"
#include <iostream>
#include <limits>
#include <iomanip>

void Renderer::Draw(const Board& playerBoard, const Board& opponentBoard, int shipCount, int boardSize) 
{
    system("cls");

    if(shipCount != -1)
    {
        std::cout<<"You and your opponent both have "<<shipCount;
        if(shipCount == 1) std::cout<<" ship ";
        else std::cout<<" ships ";
        std::cout<<"in this game\n";
    }
    
    std::cout << "           You            ";
    std::cout << "            Opponent";
    std::cout << std::endl;
    
    std::cout << "  ";
    for (char c = 'A'; c < 'A' + boardSize; ++c)
    {
        std::cout << " " << c;
    }

    std::cout << "        ";

    std::cout << "  ";
    for (char c = 'A'; c < 'A' + boardSize; ++c)
    {
        std::cout << " " << c;
    }

    std::cout << std::endl;

    for (int y = 1; y <= boardSize; ++y) 
    {
        std::cout << std::setw(2) << y;
        for (int x = 0; x < boardSize; ++x) 
        {
            char symbol = playerBoard.getSymbolAt(x, y - 1);
            std::cout << " " << symbol;
        }

        std::cout << "        ";

        std::cout << std::setw(2) << y;
        for (int x = 0; x < boardSize; ++x) 
        {
            char symbol = opponentBoard.getSymbolAt(x, y - 1);
            std::cout << " " << symbol;
        }

        std::cout << std::endl;
    }
}

void Renderer::ShowEndScreen(bool won, const Game& game){
    system("cls");

    std::cout<<"\n\n\n";
    std::cout<<(won ? " YOU WIN!!!" : "YOU LOSE!!!")<<"\n";
    std::cout<<"\n\n";

    std::cout<<"Your Game Statistics:\n";
    std::cout<<"----------------------\n";
    std::cout<<game;

    std::cout << "Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
