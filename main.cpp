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

    game.setDifficultyLevel(DifficultyLevel::Easy);

    game.setPlayerBoard(playerBoard);
    game.setOpponentBoard(opponentBoard);

    int shipCount = std::rand() % 4 + 1;
    game.setShipCount(shipCount);
    
    std::vector<int> shipLengths;
    for(int i=0; i<shipCount; ++i){
        int length = std::rand() % 4 + 2;
        shipLengths.push_back(length);
    }

    playerBoard->placeGameShips(shipLengths);
    opponentBoard->placeGameShips(shipLengths);

    game.changeState(new PlayerTurnState());
    game.run();
    
    return 0;
}
