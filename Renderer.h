#pragma once
#include "Board.h"
#include "Game.h"

class Renderer 
{
public:
    static void Draw(const Board& playerBoard, const Board& opponentBoard, int shipCount = -1);
    static void ShowEndScreen (bool won, const Game& game);
};