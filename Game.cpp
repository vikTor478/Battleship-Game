#include "Game.h"
#include "GameState.h"
#include <iostream>

Game::Game() : shipCount(0), playerBoard(nullptr), opponentBoard(nullptr), currentState(nullptr), running(true) {}

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

void Game::setShipCount(int count){
    shipCount = count;
}

int Game::getShipCount() const{
    return shipCount;
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

Board* Game::getPlayerBoard()
{
    return playerBoard;
}

Board* Game::getOpponentBoard()
{
    return opponentBoard;
}