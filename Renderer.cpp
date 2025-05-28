#include "Renderer.h"
#include <iostream>

void Renderer::Draw(const Board& playerBoard, const Board& opponentBoard) 
{
    system("cls");
    
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

    for (int x = 1; x <= 10; ++x) 
    {
        if (x < 10)
        {
            std::cout << " " << x;
        }
        else
        {
            std::cout << x;
        }

        for (int y = 0; y < 10; ++y) 
        {
            CellState state = playerBoard.GetCellState(x - 1, y);;
            char symbol = '~';
            if (state == Ship) symbol = 'S';
            else if (state == Hit) symbol = 'X';
            else if (state == Miss) symbol = 'o';

            std::cout << " " << symbol;
        }

        std::cout << "        ";
        if (x < 10)
        {
            std::cout << " " << x;
        }
        else
        {
            std::cout << x;
        }
        for (int y = 0; y < 10; ++y) 
        {
            CellState state = opponentBoard.GetCellState(x - 1, y);;
            char symbol = '~';
            if (state == Ship) symbol = 'S';
            else if (state == Hit) symbol = 'X';
            else if (state == Miss) symbol = 'o';

            std::cout << " " << symbol;
        }
        std::cout << std::endl;
    }
}
