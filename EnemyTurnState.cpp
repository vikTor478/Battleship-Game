#include "EnemyTurnState.h"
#include "PlayerTurnState.h"
#include "Game.h"
#include <iostream>

void EnemyTurnState::enter(Game& game)
{
    std::cout << "--- Enemy Turn Started ---\n";
}

void EnemyTurnState::update(Game& game)
{
    std::cout << "Enemy turn logic\n";

    //game.changeState(new PlayerTurnState());
}

void EnemyTurnState::exit(Game& game)
{
    std::cout << "--- Enemy turn ended ---\n";
}