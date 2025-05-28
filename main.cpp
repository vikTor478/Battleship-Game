#include "Game.h"
#include "PlayerTurnState.h"
#include "Board.h"
#include "Renderer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    Game game;
    Board* playerBoard = new Board();
    Board* opponentBoard = new Board();

    game.setPlayerBoard(playerBoard);
    game.setOpponentBoard(opponentBoard);

    game.changeState(new PlayerTurnState());
    game.run();
    
    return 0;
}
