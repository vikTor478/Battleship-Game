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

void Board::PlaceShip(int x, int y, int length, bool horizontal) 
{
    for (int i = 0; i < length; ++i) 
    {
        int nx = x + (horizontal ? i : 0);
        int ny = y + (horizontal ? 0 : i);
        grid[nx][ny] = Ship;
    }
}

void Board::MarkHit(int x, int y) 
{
    if (grid[x][y] == Ship)
    {
        grid[x][y] = Hit;
    }    
    else
    {
        grid[x][y] = Miss;
    }
}

CellState Board::GetCellState(int x, int y) const 
{
    return grid[x][y];
}
