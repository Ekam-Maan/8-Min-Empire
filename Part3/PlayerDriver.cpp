#include <iostream>
#include "../Part1/Map.cpp"
#include "Player.cpp"

int main()
{
    Graph *graph = new Graph(4);

    addEdge(graph, 0, 3,1);
    addEdge(graph, 1, 2,0);

    Player *player1 = new Player(graph, "Smit", 12, 13, 40);
    Player *player2 = new Player(graph, "Sanyam", 12, 13, 40);

    player1->display();
    
    player1->PLaceNewArmies(10,1);

    player1->display();

    player1->PayCoin(20);
    player1->PayCoin(2);
    player1->display();
    //player1->BuildCity(1);
    player1->DestroyArmy(1);
    player1->DestroyArmy(2);

    player1->MoveArmies(4,1,2);
    player1->MoveArmies(4,1,3);
    player1->display();

    return 0;
}