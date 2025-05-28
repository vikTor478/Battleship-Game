#pragma once
#include "Board.h"

class Renderer 
{
public:
    static void Draw(const Board& playerBoard, const Board& opponentBoard, int shipCount = -1);
    static void ShowEndScreen (bool won);
};