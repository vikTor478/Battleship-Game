#include "PlayerTurnState.h"
#include "EnemyTurnState.h"
#include "Game.h"
#include <iostream>

void PlayerTurnState::enter(Game& game)
{
    std::cout << "=== Player turn started ===\n";
}

void PlayerTurnState::update(Game& game)
{
    std::cout << "=== Shot Logic ===\n";
    std::cout << "=== Shot output ===\n";
    game.changeState(new EnemyTurnState());
}

void PlayerTurnState::exit(Game& game)
{
    std::cout << "=== Player turn ended ===\n";
}