#pragma once
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
    void MarkHit(int x, int y);
    void PlaceShip(int x, int y, int length, bool horizontal);
    CellState GetCellState(int x, int y) const;

private:
    static const int SIZE = 10;
    CellState grid[SIZE][SIZE];
};