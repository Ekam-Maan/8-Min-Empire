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
    Game();
    Game(Game* obj);
    Game& operator = (Game* obj);
    friend ostream& operator << (ostream& out, Game* obj);
    int getstash();
    void setstash(int num);
    void loop();
    void DecideWinner();

    ~Game();
};



