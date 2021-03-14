#include "biddingfacility.cpp"
#include <iostream>

using namespace std;

// #include "../Part1/Map.h"
// #include "../Part4/Cards.h"

int main()
{   
    Graph *graph = new Graph(4);

    addEdge(graph, 0, 3,1);
    addEdge(graph, 1, 2,0);

    Hand* hand = new Hand();


    biddingfacility b;

    Player *player1 = new Player(graph, "Smit Desai", 12, 13, 40,hand);
    Player *player2 = new Player(graph, "Sanyam Kadd", 12, 13, 40,hand);
    Player *player3 = new Player(graph, "Rosh Mand", 12, 13, 40,hand);
    Player *player4 = new Player(graph, "Rajat Arora", 12, 13, 40,hand);

    Player players[] = {*player1,*player2,*player3,*player4};

    queue<Player> q = b.bid(players,4);

    while ( !q.empty() )
    {
        Player p = q.front();   
        cout<<p.getname()<<"     ";
        q.pop();
    }

    return 0;
}