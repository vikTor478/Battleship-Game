#include "Board.h"
#include "Game.h"
#include <iostream>
#include <string>
#include "InputParseHandler.h"
#include <algorithm>

Board::Board()
{
    int size = 10;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            grid[i][j] = Empty;
        }
    } 
}

Board::Board(int size) 
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            grid[i][j] = Empty;
        }
    }  
}

void Board::placeGameShips(const std::vector<int>& shipLengths, int boardSize){
    ships.clear();

    for(int length : shipLengths){
        bool placed = false;

        while(!placed){
            bool horizontal = std::rand() % 2 == 0;
            int x = std::rand() % boardSize;
            int y = std::rand() % boardSize;

            if(canPlaceShip(x, y, length, horizontal, boardSize))
            {
                placeShip(x, y, length, horizontal);
                ships.push_back(ShipData(x, y, length, horizontal));
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

bool Board::markHit(int x, int y, Game& game) 
{
    std::cout << "\n\nTargeted cell " << InputParseHandler::parseToString(x, y, game.getBoardSize()) << "\n";

    if (grid[x][y] == Ship)
    {
        grid[x][y] = Hit;

        for (ShipData& ship : ships)
        {
            if (!ship.isSunk() && ship.contains(x, y))
            {
                ship.hits++;
                if (ship.isSunk()) 
                {
                    std::cout << "Ship sunk!\n";
                    markSurroundingCellsAsMiss(ship.coordinates, game.getBoardSize());
                }
                break;
            }
        }

        std::cout << "\nHIT at " << InputParseHandler::parseToString(x, y, game.getBoardSize()) << "\n";
        return true;
    }    
    else
    {
        grid[x][y] = Miss;
        std::cout << "\nMISS at " << InputParseHandler::parseToString(x, y, game.getBoardSize()) << "\n";
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

char Board::getSymbolAt(int x, int y) const 
{
    switch(getCellState(x, y))
    {
        case Empty:
            return '~';

        case Miss:
            return 'o';

        case Ship:
            return 'S';
        
        case Hit:
            return 'X';

        default:
            return ' ';
    }
}

bool Board::wasAlreadyShot(int x, int y) const
{
    return getCellState(x, y) == Miss || getCellState(x, y) == Hit;
}

bool Board::canPlaceShip(int x, int y, int length, bool horizontal, int boardSize){
    int dx = horizontal ? 1 : 0;
    int dy = horizontal ? 0 : 1;

    for(int i=0; i<length; ++i)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;

        if(nx<0 || ny<0 || nx>=boardSize || ny>=boardSize)
        return false;

        for(int ix = nx - 1; ix <= nx + 1; ++ix){
            for(int iy = ny - 1; iy <= ny + 1; ++ iy){
                if(ix >= 0 && iy >= 0 && ix < boardSize && iy < boardSize){
                    if(grid[ix][iy] == Ship)
                    return false;
                }
            }
        }
    }
    return true;
}

void Board::markSurroundingCellsAsMiss(const std::vector<std::pair<int, int>>& shipCoords, int boardSize)
{
    for (const auto& [x, y] : shipCoords)
    {
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= boardSize || ny < 0 || ny >= boardSize)
                    continue;

                if (std::find(shipCoords.begin(), shipCoords.end(), std::make_pair(nx, ny)) != shipCoords.end())
                    continue;

                if (grid[nx][ny] == Empty)
                {
                    grid[nx][ny] = Miss;
                }
            }
        }
    }
}

