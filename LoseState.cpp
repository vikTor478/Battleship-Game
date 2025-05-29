#include "LoseState.h"
#include "Game.h"
#include "Renderer.h"

void LoseState::enter(Game& game){
    Renderer::ShowEndScreen(false, game);
    game.quit();
}

void LoseState::update(Game& game){}

void LoseState::exit(Game& game){}