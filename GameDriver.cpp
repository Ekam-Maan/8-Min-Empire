#include "GameEngine.h"
#include<iostream>
int main()
{
    Game game;

    game.loop();

    game.DecideWinner();

    return 0;
}

//Cards.cpp {delete deck} - need to check if this breaks anything or not

/*
    Phase Observer:
        Both players act as seperate subjects
        and subjects have one phase observer attached to them  : Game.cpp default construtor
        As subject's phase changes, obersers are notified : 
            The following places are uses the phase obeserver in player.cpp 
                PayCoin
*/