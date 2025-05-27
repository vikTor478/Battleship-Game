#include "Game.h"
#include "GameState.h"
#include <iostream>

Game::Game() : playerBoard(nullptr), opponentBoard(nullptr), currentState(nullptr), running(true) {}

Game::~Game()
{
    delete playerBoard;
    delete opponentBoard;

    if (currentState)
    {
        currentState -> exit(*this);
        delete currentState;
    }
}

void Game::changeState(GameState* newState)
{
    if (currentState)
    {
        currentState -> exit(*this);
        delete currentState;
    }
    currentState = newState;
    currentState -> enter(*this);
}

void Game::run()
{
    while (running && currentState)
    {
        currentState -> update(*this);
    }
}

void Game::quit()
{
    running = false;
}

void Game::setDifficultyLevel(DifficultyLevel level)
{
    difficultyLevel = level;
}

void Game::setPlayerBoard(Board* board)
{
    if(playerBoard) { delete playerBoard; }
    playerBoard = board;
}

void Game::setOpponentBoard(Board* board)
{
    if(opponentBoard) { delete opponentBoard; }
    opponentBoard = board;
}

DifficultyLevel Game::getDifficultyLevel() const
{
    return difficultyLevel;
}

Board* Game::getPlayerBoard()
{
    return playerBoard;
}

Board* Game::getOpponentBoard()
{
    return opponentBoard;
}