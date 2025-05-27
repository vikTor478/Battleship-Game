#include "Game.h"
#include "GameState.h"
#include <iostream>

Game::Game() : currentState(nullptr), running(true) {}

Game::~Game()
{
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