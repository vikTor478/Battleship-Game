#ifndef GAME_H
#define Game_H

#include "Board.h"

enum DifficultyLevel 
{
    Easy,
    Medium,
    Hard,
};

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void changeState(GameState* newState);
    void quit();

    void setDifficultyLevel(DifficultyLevel difficultyLevel);
    void setPlayerBoard(Board* playerBoard);
    void setOpponentBoard(Board* opponentBoard);

    DifficultyLevel getDifficultyLevel() const;
    Board* getPlayerBoard();
    Board* getOpponentBoard();

    void setShipCount(int count);
    int getShipCount() const;

private:
    DifficultyLevel difficultyLevel;
    int shipCount;
    GameState* currentState;
    Board* playerBoard;
    Board* opponentBoard;
    bool running;
};

#endif
