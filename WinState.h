#pragma once
#include "GameState.h"

class WinState : public GameState{
    public:
    void enter(Game& game) override;
    void update(Game& game) override;
    void exit(Game& game) override;
};