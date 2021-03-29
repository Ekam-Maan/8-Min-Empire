#pragma once

#include "MapLoader.h"
#include "Player.h"   
#include "Cards.h"
#include "biddingfacility.h"

class Game
{
private:
    int stash;
    Player* one;
    Player* two;
    bool playerone_turn;
    Graph* graph;
    Hand* hand;
    biddingfacility* bidfac;

public:
    int getstash();
    void setstash(int num);
    void loop();
    void DecideWinner();
    Game();
    ~Game();
};



