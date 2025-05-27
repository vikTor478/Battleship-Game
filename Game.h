#ifndef GAME_H
#define Game_H

class GameState;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void changeState(GameState* newState);
    void quit();

private:
    GameState* currentState;
    bool running;
};

#endif
