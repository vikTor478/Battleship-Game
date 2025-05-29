#ifndef BOARD_H
#define BOARD_H

#include "ShipData.h"
#include <iostream>
#include <string>
#include <vector>

enum CellState 
{
    Empty,
    Ship,
    Hit,
    Miss
};

class Board 
{
public:
    Board();
    ~Board();

    bool markHit(int x, int y);
    void placeShip(int x, int y, int length, bool horizontal);
    CellState getCellState(int x, int y) const;
    std::string getSymbolAt(int x, int y) const;
    bool wasAlreadyShot(int x, int y) const;

    const std::vector<ShipData>& getShips() const;

    void placeGameShips(const std::vector<int>& shipLengths);

    bool allShipsSunk() const;

private:
    static const int SIZE = 10;
    CellState grid[SIZE][SIZE];
    std::vector<ShipData> ships;
    bool canPlaceShip(int x, int y, int length, bool horizontal);
};

#endif