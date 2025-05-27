#include "PlayerTurnState.h"
#include "EnemyTurnState.h"
#include "Renderer.h"
#include "Game.h"
#include <iostream>

void PlayerTurnState::enter(Game& game)
{
    if (game.getPlayerBoard() && game.getOpponentBoard()) 
    {
        Renderer::Draw(*game.getPlayerBoard(), *game.getOpponentBoard());
        std::cout << "=== Player turn started ===\n";
    } 
    else 
    {
        std::cerr << "Error: boards are bot initialized\n";
    }
}

void PlayerTurnState::update(Game& game)
{
    std::cout << "=== Shot Logic ===\n";
    std::cin.get();  
    game.changeState(new EnemyTurnState());
}

void PlayerTurnState::exit(Game& game)
{
    std::cout << "=== Player turn ended ===\n";
}