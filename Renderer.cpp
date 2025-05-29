#include "Renderer.h"
#include <iostream>
#include <limits>

void Renderer::Draw(const Board& playerBoard, const Board& opponentBoard, int shipCount) 
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
    for (char c = 'A'; c <= 'J'; ++c)
    {
        std::cout << " " << c;
    }

    std::cout << "        ";

    std::cout << "  ";
    for (char c = 'A'; c <= 'J'; ++c)
    {
        std::cout << " " << c;
    }

    std::cout << std::endl;

    for (int y = 1; y <= 10; ++y) 
    {
        if (y < 10)
        {
            std::cout << " " << y;
        }
        else
        {
            std::cout << y;
        }

        for (int x = 0; x < 10; ++x) 
        {
            CellState state = playerBoard.getCellState(x, y - 1);;
            char symbol = '~';
            if (state == Ship) symbol = 'S';
            else if (state == Hit) symbol = 'X';
            else if (state == Miss) symbol = 'o';

            std::cout << " " << symbol;
        }

        std::cout << "        ";
        if (y < 10)
        {
            std::cout << " " << y;
        }
        else
        {
            std::cout << y;
        }
        for (int x = 0; x < 10; ++x) 
        {
            CellState state = opponentBoard.getCellState(x, y - 1);;
            char symbol = '~';
            if (state == Ship) symbol = 'S';
            else if (state == Hit) symbol = 'X';
            else if (state == Miss) symbol = 'o';

            std::cout << " " << symbol;
        }
        std::cout << std::endl;
    }
}

void Renderer::ShowEndScreen(bool won){
    system("cls");

    std::cout<<"\n\n\n";
    std::cout<<(won ? "           YOU WIN!!!           " : "           YOU LOSE!!!           ")<<"\n";
    std::cout<<"\n\n";

    std::cout << "Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
