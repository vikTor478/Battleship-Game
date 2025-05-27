#include "Game.h"
#include "PlayerTurnState.h"
#include "Board.h"
#include "Renderer.h"
#include <iostream>

int main()
{
    Game game;
    Board playerBoard;
    Board opponentBoard;
    game.changeState(new PlayerTurnState());
    game.run();
    playerBoard.PlaceShip(1, 1, 4, true);
    playerBoard.MarkHit(2, 3);
    Renderer::Draw(playerBoard, opponentBoard);
    std::cin.get();  
    system("cls");
    playerBoard.MarkHit(4, 4);
    Renderer::Draw(playerBoard, opponentBoard);
    std::cin.get();
    return 0;
}
