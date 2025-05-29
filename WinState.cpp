#include "WinState.h"
#include "Game.h"
#include "Renderer.h"

void WinState::enter(Game& game){
    Renderer::ShowEndScreen(true, game);
    game.quit();
}

void WinState::update(Game& game){}

void WinState::exit(Game& game){}