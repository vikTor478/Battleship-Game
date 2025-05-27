#ifndef GAME_H
#define Game_H

#include "Board.h"

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void changeState(GameState* newState);
    void quit();

    void setPlayerBoard(Board* playerBoard);
    void setOpponentBoard(Board* opponentBoard);

    Board* getPlayerBoard();
    Board* getOpponentBoard();

private:
    GameState* currentState;
    Board* playerBoard;
    Board* opponentBoard;
    bool running;
};

#endif
