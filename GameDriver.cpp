#include "Game.h"
#include<iostream>;
int main()
{
    Game game;

    game.loop();

    game.DecideWinner();


    //MapLoader* ml = new MapLoader();
    //Graph* graph = ml->loadBoard();
    //Hand* hand = new Hand();

    //Player* p1 = new Player(graph, "Player1", 3, 14, 18, hand);
    //Player* p2 = new Player(graph, "Player2", 3, 14, 18, hand);

    //std::cout << "=======================================\n";
    //graph->printGraph();
    //
    //graph->placeNewArmies("Player1", 4, 2); // place 4 armies at id 2
    //graph->buildCity("Player1", 2);
    //graph->moveArmies("Player1", 2, 2, 1); // moving 2 armies form id 2 to id 1
   
    //graph->placeNewArmies("Player2", 7, 5);// place 7 armies at id 5
    //graph->buildCity("Player2", 5);
    //
    //graph->moveArmies("Player2", 3, 5, 7); // moving 3 armies from id 5 to id 7
   
   
    //

    //std::cout << "\n\n===============Showing Details after the performing the moves==================\n\n";
    //graph->printGraph();


    //delete ml;
    //delete graph;
    //delete hand;
    //delete p1;
    //delete p2;
    //hand = NULL;
    //ml = NULL;
    //graph = NULL;
    //p1 = p2 = NULL;

    return 0;
}