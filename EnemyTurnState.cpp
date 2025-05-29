#include "EnemyTurnState.h"
#include "PlayerTurnState.h"
#include "LoseState.h"
#include "Renderer.h"
#include "Game.h"
#include "InputParseHandler.h"
#include <iostream>
#include <chrono>
#include <thread>


void showThinkingAnimation() 
{
    std::string base = "Opponent's turn";
    std::string dots[] = {".  ", ".. ", "..."};

    for (int i = 0; i < 3; ++i) 
    {
        for (const std::string& d : dots) 
        {
            std::cout << "\r" << base << d << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
}

void EnemyTurnState::enter(Game& game)
{
    if (game.getPlayerBoard() && game.getOpponentBoard()) 
    {
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard(), game.getShipCount());
        std::cout << "--- Enemy Turn Started ---\n";
    } 
    else 
    {
        std::cerr << "Error: boards are not initialized\n";
    }
}

void EnemyTurnState::update(Game& game)
{
    std::pair<int, int> targetCell;

    showThinkingAnimation();

    switch (game.getDifficultyLevel()) 
    {
        case DifficultyLevel::Easy:
            targetCell = performEasyAI(game);
            break;

        case DifficultyLevel::Medium:
            targetCell = performMediumAI(game);
            break;

        case DifficultyLevel::Hard:
            targetCell = performHardAI(game);
            break;
    }

    if(game.getPlayerBoard() -> getCellState(targetCell.first, targetCell.second) == Hit)
    {
        game.changeState(new EnemyTurnState());
    }
    else
    {
       game.changeState(new PlayerTurnState());
    }
}

void EnemyTurnState::exit(Game& game)
{
    std::cout << "--- Enemy turn ended ---\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

std::pair<int, int> EnemyTurnState::performEasyAI(Game& game) 
{
    Board* playerBoard = game.getPlayerBoard();
    int x, y;

    do 
    {
        x = rand() % 10;
        y = rand() % 10;
    } 
    while (playerBoard->wasAlreadyShot(x, y));

    playerBoard -> markHit(x, y);
    return { x, y };
}

std::pair<int, int> EnemyTurnState::performMediumAI(Game& game) 
{
    Board* playerBoard = game.getPlayerBoard();

    if (!Game::targetQueue.empty()) 
    {
        auto [x, y] = Game::targetQueue.back();
        Game::targetQueue.pop_back();

        if (!playerBoard -> wasAlreadyShot(x, y)) 
        {
            bool hit = playerBoard->markHit(x, y);
            if (hit) 
            {
                enqueueAdjacentTargets(x, y, playerBoard);
            }
            return { x, y };
        }
    }


    int x, y;
    do 
    {
        x = rand() % 10;
        y = rand() % 10;
    } 
    while (playerBoard -> wasAlreadyShot(x, y));

    bool hit = playerBoard -> markHit(x, y);
    if (hit) 
    {
        enqueueAdjacentTargets(x, y, playerBoard);
    }
    return { x, y };
}

std::pair<int, int> EnemyTurnState::performHardAI(Game& game) 
{
    Board* playerBoard = game.getPlayerBoard();

    if (!Game::targetQueue.empty()) 
    {
        auto [x, y] = Game::targetQueue.back();
        Game::targetQueue.pop_back();

        if (!playerBoard -> wasAlreadyShot(x, y)) 
        {
            bool hit = playerBoard -> markHit(x, y);
            if (hit) 
            {
                enqueueAdjacentTargets(x, y, playerBoard);
            }
            return { x, y };
        }
    }

    int x, y;
    do 
    {
        x = rand() % 10;
        y = rand() % 10;
    } 
    while ((x + y) % 2 != 0 || playerBoard -> wasAlreadyShot(x, y));

    bool hit = playerBoard -> markHit(x, y);
    if (hit) 
    {
        enqueueAdjacentTargets(x, y, playerBoard);
    }
    return { x, y };
}

void EnemyTurnState::enqueueAdjacentTargets(int x, int y, Board* board) 
{
    if (x > 0 && !board -> wasAlreadyShot(x - 1, y)) Game::targetQueue.emplace_back(x - 1, y);
    if (x < 9 && !board -> wasAlreadyShot(x + 1, y)) Game::targetQueue.emplace_back(x + 1, y);
    if (y > 0 && !board -> wasAlreadyShot(x, y - 1)) Game::targetQueue.emplace_back(x, y - 1);
    if (y < 9 && !board -> wasAlreadyShot(x, y + 1)) Game::targetQueue.emplace_back(x, y + 1);
}
