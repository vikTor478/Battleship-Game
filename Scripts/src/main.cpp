#include "Game.h"
#include "MainMenuState.h"
#include "Board.h"
#include "Renderer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game game;

    game.changeState(new States::MainMenuState());
    game.run();
}
