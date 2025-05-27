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

    void setShipCount(int count);
    int getShipCount() const;

private:
    int shipCount;
    GameState* currentState;
    Board* playerBoard;
    Board* opponentBoard;
    bool running;
};

#endif
