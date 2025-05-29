#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <iostream>

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

    void incrementPlayerTurn();
    void incrementPlayerHit();
    void incrementPlayerMiss();

    int getPlayerTurns() const;
    int getPlayerHits() const;
    int getPlayerMisses() const;
    double getPlayerAccuracy() const;

    Game& operator++();

    operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);

private:
    DifficultyLevel difficultyLevel;
    int shipCount;
    GameState* currentState;
    Board* playerBoard;
    Board* opponentBoard;
    bool running;
    int playerTurns = 0;
    int playerHits = 0;
    int playerMisses = 0;
};

#endif
