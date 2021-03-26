#include "Game.h"
 
int main()
{
    Game game;

    game.loop();

    game.DecideWinner();

    return 0;
}