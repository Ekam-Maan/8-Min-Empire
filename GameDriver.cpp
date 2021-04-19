#include "GameEngine.h"
#include<iostream>
int main()
{
    Game game;

    game.loop();

    game.DecideWinner();

    char ch;
    cout << "Press any character to exit";
    cin >> ch;

    return 0;
}

/*
    Phase Observer:
        Both players act as seperate subjects
        and subjects have one phase observer attached to them  : Game.cpp default construtor
        As subject's phase changes, obersers are notified : 
            The following places are uses the phase obeserver in player.cpp 
                Pickcard
*/