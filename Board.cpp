#include "Board.h"
#include <iostream>

Board::Board() 
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            grid[i][j] = Empty;
        }
    }  
}

Board::~Board()
{
    std::cout << "Board removed\n";
}

void Board::placeShip(int x, int y, int length, bool horizontal) 
{
    for (int i = 0; i < length; ++i) 
    {
        int nx = x + (horizontal ? i : 0);
        int ny = y + (horizontal ? 0 : i);
        grid[nx][ny] = Ship;
    }
}

bool Board::markHit(int x, int y) 
{
    if (grid[x][y] == Ship)
    {
        grid[x][y] = Hit;
        return true;
    }    
    else
    {
        grid[x][y] = Miss;
        return false;
    }
}

CellState Board::getCellState(int x, int y) const 
{
    return grid[x][y];
}

bool Board::wasAlreadyShot(int x, int y) const
{
    return getCellState(x, y) == Miss || getCellState(x, y) == Hit;
}
