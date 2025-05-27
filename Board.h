#ifndef BOARD_H
#define BOARD_H

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
    bool wasAlreadyShot(int x, int y) const;

private:
    static const int SIZE = 10;
    CellState grid[SIZE][SIZE];
};

#endif