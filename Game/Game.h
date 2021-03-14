#include "../Part1/Map.h"
#include "../Part3/Player.h"   
#include "../Part4/Cards.h"
#include "../Part5/biddingfacility.cpp"
#include <queue>

class Game
{
    private:
        int stash;
        Player* players;
        int numOfPlayers;
        queue<Player> Queue;
        Graph *graph;
        Hand *hand;
        biddingfacility *bidfac;

    public:
        int getstash() { return stash; }
        void setstash( int num ) { stash = num; }
        void showQ();
        Game();
        ~Game();
};


