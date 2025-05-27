#ifndef ENEMY_TURN_STATE_H
#define ENEMY_TURN_STATE_H

#include "PlayerTurnState.h"

class EnemyTurnState : public PlayerTurnState
{
public:
    void enter(Game& game) override;
    void update(Game& game) override;
    void exit(Game& game) override;
};

#endif