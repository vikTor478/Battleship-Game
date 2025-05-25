#include "Board.h"
#include "Renderer.h"
#include <iostream>

int main()
{
    Board playerBoard;
    Board opponentBoard;
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
