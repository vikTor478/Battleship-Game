#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "GameState.h"
#include <iostream>

using namespace States;

enum DifficultyLevel 
{
    Easy,
    Medium,
    Hard,
};

enum GameMode
{
    Standart,
    RandomShips,
};

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void changeState(States::GameState* newState);
    void quit();

    void setBoardSize(int size);
    void setDifficultyLevel(DifficultyLevel difficultyLevel);
    void setGameMode(GameMode gameMode);
    void setPlayerBoard(Board* playerBoard);
    void setOpponentBoard(Board* opponentBoard);

    int getBoardSize();
    DifficultyLevel getDifficultyLevel() const;
    GameMode getGameMode() const;
    Board* getPlayerBoard();
    Board* getOpponentBoard();

    void setShipCount(int count);
    int getShipCount() const;
    std::vector<std::pair<int, int>> targetQueue;
    std::vector<std::pair<int, int>> currentHits;  
    std::string orientation = "none";

    void incrementPlayerTurn();
    void incrementPlayerHit();
    void incrementPlayerMiss();

    int getPlayerTurns() const;
    int getPlayerHits() const;
    int getPlayerMisses() const;
    double getPlayerAccuracy() const;

    void fullRestart();

    Game& operator++();

    operator bool() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);

private:
    DifficultyLevel difficultyLevel = Easy;
    GameMode gameMode = Standart;
    int shipCount;
    int boardSize = 0;
    States::GameState* currentState;
    Board* playerBoard;
    Board* opponentBoard;
    bool running;
    int playerTurns = 0;
    int playerHits = 0;
    int playerMisses = 0;
};

#endif
