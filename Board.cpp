#include "Board.h"
#include <iostream>
#include <string>
#include "InputParseHandler.h"

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

void Board::placeGameShips(const std::vector<int>& shipLengths){
    ships.clear();

    for(int length : shipLengths){
        bool placed = false;

        while(!placed){
            bool horizontal = std::rand() % 2 == 0;
            int x = std::rand() % SIZE;
            int y = std::rand() % SIZE;

            if(canPlaceShip(x, y, length, horizontal)){
                placeShip(x, y, length, horizontal);
                ships.push_back(ShipData(length));
                placed = true;
            }
        }
    }
}

const std::vector<ShipData>& Board::getShips() const{
    return ships;
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
    std::cout << "Opponent targeted cell " << InputParseHandler::parseToString(x, y) << "\n";

    if (grid[x][y] == Ship)
    {
        grid[x][y] = Hit;

        for(ShipData& ship : ships)
        {
            if(!ship.isSunk())
            {
                ship.hits++;
                break;
            }
        }
        std::cout << "HIT at " << InputParseHandler::parseToString(x, y) << "\n";
        return true;
    }    
    else
    {
        grid[x][y] = Miss;
        std::cout << "MISS at " << InputParseHandler::parseToString(x, y) << "\n";
        return false;
    }
}

bool Board::allShipsSunk() const{
    for(const ShipData& ship : ships){
        if(!ship.isSunk()) return false;
    }
    return true;
}

CellState Board::getCellState(int x, int y) const 
{
    return grid[x][y];
}

std::string Board::getSymbolAt(int x, int y) const 
{
    switch(getCellState(x, y))
    {
        case Empty:
            return "~";

        case Miss:
            return "o";

        case Ship:
            return "S";
        
        case Hit:
            return "X";

        default:
            return " ";
    }
}

bool Board::wasAlreadyShot(int x, int y) const
{
    return getCellState(x, y) == Miss || getCellState(x, y) == Hit;
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
