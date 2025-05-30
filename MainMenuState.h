#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "GameState.h"

class MainMenuState : public GameState
{
public:
    virtual void enter(Game& game) override;
    virtual void update(Game& game) override;
    virtual void exit(Game& game) override;
};

void showSettings(Game& game);
void selectDifficulty(Game& game);
void selectBoardSize(Game& game);
void selectGameMode();
void showRules();

#endif