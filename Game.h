#pragma once

#include "MapLoader.h"
#include "Player.h"   
#include "Cards.h"
#include "biddingfacility.h"
#include <queue>

class Game
{
private:
    int stash;
    Player* players;
    int numOfPlayers;
    queue<Player> Queue;
    Graph* graph;
    Hand* hand;
    biddingfacility* bidfac;

public:
    int getstash();
    void setstash(int num);
    void showQ();
    void loop();
    bool GameEnded();
    void DecideWinner();
    Game();
    ~Game();
};



