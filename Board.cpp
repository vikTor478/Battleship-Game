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

void Board::generateShips(int shipCount){
    ships.clear();

    for (int i = 0; i < shipCount; ++i) {
       int length = std::rand() % 4 + 2;
    
       ships.push_back(ShipData(length));
    }
}

const std::vector<ShipData>& Board::getShips() const{
    return ships;
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

bool Board::canPlaceShip(int x, int y, int length, bool horizontal){
    int dx = horizontal ? 1 : 0;
    int dy = horizontal ? 0 : 1;

    for(int i=0; i<length; ++i){
        int nx = x + i * dx;
        int ny = y + i * dy;

        if(nx<0 || ny<0 || nx>=SIZE || ny>=SIZE)
        return false;

        for(int ix = nx - 1; ix <= nx + 1; ++ix){
            for(int iy = ny - 1; iy <= ny + 1; ++ iy){
                if(ix >= 0 && iy >= 0 && ix < SIZE && iy < SIZE){
                    if(grid[ix][iy] == Ship)
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::generatePlayerShips(int shipCount){
    ships.clear();

    int placed = 0;

    while (placed < shipCount) {
        int length = std::rand() % 4 + 2;
        bool horizontal = std::rand() % 2 == 0;

        int x = std::rand() % SIZE;
        int y = std::rand() % SIZE;

        if (canPlaceShip(x, y, length, horizontal)) {
            PlaceShip(x, y, length, horizontal);
            ships.push_back(ShipData(length));
            ++placed;
        }
    }
}