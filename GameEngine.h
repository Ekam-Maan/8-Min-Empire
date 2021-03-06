#pragma once
#include "MapLoader.h"
#include "Player.h"   
#include "Cards.h"
#include "biddingfacility.h"
#include "GameObservers.h"


class Game
{
private:
    int stash;
    Player* one;
    Player* two;
    Observer* PlayerOneObs;
    Observer* PlayerTwoObs;
    bool playerone_turn;
    Graph* graph;
    Hand* hand;
    biddingfacility* bidfac;

public:
    int mode;// 1 represents single game mode and 2 represents the tournament mode
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




