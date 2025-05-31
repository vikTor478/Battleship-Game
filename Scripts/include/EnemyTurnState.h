#ifndef ENEMY_TURN_STATE_H
#define ENEMY_TURN_STATE_H

#include "PlayerTurnState.h"
#include <vector>
#include <utility>
#include "Board.h"

namespace States
{
    class EnemyTurnState : public PlayerTurnState
    {
    public:
        void enter(Game& game) override;
        void update(Game& game) override;
        void exit(Game& game) override;

        std::pair<int, int> performEasyAI(Game& game);
        std::pair<int, int> performMediumAI(Game& game);
        std::pair<int, int> performHardAI(Game& game);
        
        void enqueueAdjacentTargets(int x, int y, Board* board, Game& game);
        void enqueueNextTarget(int x, int y, Board* board, Game& game);
    };
}
#endif