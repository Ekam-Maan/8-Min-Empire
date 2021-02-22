#include <iostream>
#include "../Part1/Map.cpp"
#include "Player.cpp"
#include "../Part4/Cards.cpp"
#include"../Part5/bidding.cpp"
#include"../Part5/player.cpp"

int main()
{ 
    Graph *graph = new Graph(4);

    addEdge(graph, 0, 3,1);
    addEdge(graph, 1, 2,0);

    Hand* hand = new Hand();
    hand->Show();

    hand->exchange(2);
    hand->Show();
    Player *player1 = new Player(graph, "Smit", 12, 13, 40,hand);
    Player *player2 = new Player(graph, "Sanyam", 12, 13, 40,hand);
    Player *player3 = new Player(graph, "Rosh", 12, 13, 40,hand);
    Player *player4 = new Player(graph, "Rajat", 12, 13, 40,hand);
    Player *player5 = new Player(graph, "Smit", 12, 13, 40,hand);
    player1->display();
    
    player1->PLaceNewArmies(10,1);

    player1->display();

    player1->PayCoin(20);
    player1->PayCoin(2);
    player1->display();
    
    player1->DestroyArmy(1);
    player1->DestroyArmy(2);

    player1->MoveArmies(4,1,2);
    player1->MoveArmies(4,1,3);
    player1->display();

    player1->BuildCity(2);
    player1->BuildCity(3);

    player1->pickCard();
    player1->displayCards();

    player1->display();
    return 0;
}