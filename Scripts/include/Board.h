#ifndef BOARD_H
#define BOARD_H

#include "ShipData.h"
#include <iostream>
#include <string>
#include <vector>

class Game;

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
    Board(int size);
    ~Board();

    bool markHit(int x, int y, Game& game);
    void placeShip(int x, int y, int length, bool horizontal);
    CellState getCellState(int x, int y) const;
    char getSymbolAt(int x, int y) const;
    bool wasAlreadyShot(int x, int y) const;

    const std::vector<ShipData>& getShips() const;

    void placeGameShips(const std::vector<int>& shipLengths, int boardSize);

    bool allShipsSunk() const;

    void markSurroundingCellsAsMiss(const std::vector<std::pair<int, int>>& shipCoords, int boardSize);

private:
    static const int SIZE = 26;
    CellState grid[SIZE][SIZE];
    std::vector<ShipData> ships;
    bool canPlaceShip(int x, int y, int length, bool horizontal, int boardSize);
};

#endif