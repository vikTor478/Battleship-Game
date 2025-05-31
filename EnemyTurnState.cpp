#include "EnemyTurnState.h"
#include "MainMenuState.h"
#include "PlayerTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include "InputParseHandler.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>


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
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard(), game.getShipCount(), game.getBoardSize());
        std::cout << "\n\n--- Enemy Turn Started ---\n";
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

    if(game.getPlayerBoard() -> allShipsSunk())
    {
        Renderer::ShowEndScreen(false, game);
        game.changeState(new MainMenuState());
        return;
    }

    if(game.getPlayerBoard() -> getCellState(targetCell.first, targetCell.second) == Hit)
    {
        std::cout << "\nThe opponent hit your ship. They shoot again...\n";
        game.changeState(new EnemyTurnState());
    }
    else
    {
        game.changeState(new PlayerTurnState());
    }
}

void EnemyTurnState::exit(Game& game)
{
    if(!game.getPlayerBoard() -> allShipsSunk())
    {
        std::cout << "\n--- Enemy turn ended ---\n";
        system("pause");
    }
    else
    {
        game.fullRestart();
        game.quit();
    }
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

    playerBoard -> markHit(x, y, game);
    return { x, y };
}

std::pair<int, int> EnemyTurnState::performMediumAI(Game& game) 
{
    Board* playerBoard = game.getPlayerBoard();

    while (!game.targetQueue.empty()) 
    {
        auto [x, y] = game.targetQueue.back();
        game.targetQueue.pop_back();

        if (!playerBoard->wasAlreadyShot(x, y)) 
        {
            bool hit = playerBoard->markHit(x, y, game);

            for (const ShipData& ship : playerBoard->getShips())
            {
                if (ship.isSunk() && ship.contains(x, y))
                {
                    game.currentHits.clear();
                    game.targetQueue.clear();      
                    game.orientation = "none";
                    hit = false;
                }
            }

            if (hit) 
            {
                game.currentHits.emplace_back(x, y);

                if (game.currentHits.size() >= 2 && game.orientation == "none") 
                {
                    if (game.currentHits[0].first == game.currentHits[1].first)
                    {
                        game.orientation = "vertical";
                    }
                    else if (game.currentHits[0].second == game.currentHits[1].second)
                    {
                        game.orientation = "horizontal";
                    }
                }

                enqueueNextTarget(x, y, playerBoard, game);
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

    bool hit = playerBoard -> markHit(x, y, game);
    if (hit) 
    {
        game.currentHits.emplace_back(x, y);
        enqueueAdjacentTargets(x, y, playerBoard, game);
    }

    for (const ShipData& ship : playerBoard -> getShips())
    {
        if(ship.contains(x, y))
        {
            if(ship.isSunk())
            {
                game.currentHits.clear();
                game.orientation = "none";
                game.targetQueue.clear();
            }
        }
    }

    return { x, y };
}

std::pair<int, int> EnemyTurnState::performHardAI(Game& game) 
{
    Board* playerBoard = game.getPlayerBoard();

    while (!game.targetQueue.empty()) 
    {
        auto [x, y] = game.targetQueue.back();
        game.targetQueue.pop_back();

        if (!playerBoard->wasAlreadyShot(x, y)) 
        {
            bool hit = playerBoard->markHit(x, y, game);

            for (const ShipData& ship : playerBoard->getShips())
            {
                if (ship.isSunk() && ship.contains(x, y))
                {
                    game.currentHits.clear();
                    game.targetQueue.clear();      
                    game.orientation = "none";
                    hit = false;
                }
            }

            if (hit) 
            {
                game.currentHits.emplace_back(x, y);

                if (game.currentHits.size() >= 2 && game.orientation == "none") 
                {
                    if (game.currentHits[0].first == game.currentHits[1].first)
                    {
                        game.orientation = "vertical";
                    }
                    else if (game.currentHits[0].second == game.currentHits[1].second)
                    {
                        game.orientation = "horizontal";
                    }
                }

                enqueueNextTarget(x, y, playerBoard, game);
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

    bool hit = playerBoard -> markHit(x, y, game);
    if (hit) 
    {
        game.currentHits.emplace_back(x, y);
        enqueueAdjacentTargets(x, y, playerBoard, game);
    }
    return { x, y };
}

void EnemyTurnState::enqueueAdjacentTargets(int x, int y, Board* board, Game& game) 
{
    if (x > 0 && !board -> wasAlreadyShot(x - 1, y)) game.targetQueue.emplace_back(x - 1, y);
    if (x < game.getBoardSize() - 1 && !board -> wasAlreadyShot(x + 1, y)) game.targetQueue.emplace_back(x + 1, y);
    if (y > 0 && !board -> wasAlreadyShot(x, y - 1)) game.targetQueue.emplace_back(x, y - 1);
    if (y < game.getBoardSize() - 1 && !board -> wasAlreadyShot(x, y + 1)) game.targetQueue.emplace_back(x, y + 1);
}

void EnemyTurnState::enqueueNextTarget(int x, int y, Board* board, Game& game) 
{
    std::sort(game.currentHits.begin(), game.currentHits.end());

    if (game.orientation == "horizontal") 
    {
        int minX = game.currentHits.front().first;
        int yVal = game.currentHits.front().second;
        int maxX = game.currentHits.back().first;

        if (minX - 1 >= 0 && !board->wasAlreadyShot(minX - 1, yVal))
        {
            game.targetQueue.push_back({ minX - 1, yVal });
        }
        if (maxX + 1 < 10 && !board->wasAlreadyShot(maxX + 1, yVal))
        {
            game.targetQueue.push_back({ maxX + 1, yVal });
        }
    }
    else if (game.orientation == "vertical") 
    {
        int xVal = game.currentHits.front().first;
        int minY = game.currentHits.front().second;
        int maxY = game.currentHits.back().second;

        if (minY - 1 >= 0 && !board->wasAlreadyShot(xVal, minY - 1))
        {
            game.targetQueue.push_back({ xVal, minY - 1 });
        }
        if (maxY + 1 < 10 && !board->wasAlreadyShot(xVal, maxY + 1))
        {
            game.targetQueue.push_back({ xVal, maxY + 1 });
        }
    }
    else
    {
        enqueueAdjacentTargets(x, y, board, game);
    }
}