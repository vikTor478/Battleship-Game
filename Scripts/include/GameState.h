#ifndef GAME_STATE_H
#define GAME_STATE_H

class Game;

namespace States
{
    class GameState
    {
    public:
        virtual ~GameState() = default;

        virtual void enter(Game& game) = 0;
        virtual void update(Game& game) = 0;
        virtual void exit(Game& game) = 0;
    };
}



#endif