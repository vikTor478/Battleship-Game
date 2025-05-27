#include "EnemyTurnState.h"
#include "PlayerTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>

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

    while(targetCellState == Miss || targetCellState == Hit)
    {
        x = std::rand() % 10;
        y = std::rand() % 10;

        targetCellState = playerBoard -> GetCellState(x, y);
    }

    playerBoard -> MarkHit(x, y);

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