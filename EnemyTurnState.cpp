#include "EnemyTurnState.h"
#include "PlayerTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>



void EnemyTurnState::enter(Game& game)
{
    if (game.getPlayerBoard() && game.getOpponentBoard()) 
    {
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard());
        std::cout << "--- Enemy Turn Started ---\n";
    } 
    else 
    {
        std::cerr << "Error: boards are bot initialized\n";
    }
}

void EnemyTurnState::update(Game& game)
{
    std::cout << "Enemy turn logic\n";
    int x = std::rand() % 10;
    int y = std::rand() % 10;

    Board* playerBoard = game.getPlayerBoard();

    CellState targetCellState = playerBoard -> GetCellState(x, y);

    showThinkingAnimation();

    while(targetCellState == Miss || targetCellState == Hit)
    {
        x = std::rand() % 10;
        y = std::rand() % 10;

        targetCellState = playerBoard -> GetCellState(x, y);
    }

    

    playerBoard -> MarkHit(x, y);

    std::cout << "Enemy target at cell B4.\n";

    if(targetCellState == Hit)
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
}

void EnemyTurnState::showThinkingAnimation() 
{
    std::string base = "Opponent thinking";
    std::string dots[] = {".  ", ".. ", "..."};

    for (int i = 0; i < 3; ++i) 
    {
        for (const std::string& d : dots) {
            std::cout << "\r" << base << d << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}