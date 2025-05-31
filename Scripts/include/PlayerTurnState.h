#ifndef PLAYER_TURN_STATE_H
#define PLAYER_TURN_STATE_H

#include "GameState.h"

namespace States
{
    class PlayerTurnState : public GameState
    {
    private:
        bool isExtraTurn = false;
    public:
        virtual void enter(Game& game) override;
        virtual void update(Game& game) override;
        virtual void exit(Game& game) override;
    };
}
#endif