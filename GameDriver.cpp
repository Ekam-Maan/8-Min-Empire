#include "Game.h"
 
int main()
{
    Game game;

    game.loop();

    game.DecideWinner();



    /*  printGraph(graph);
    graph->placeNewArmies(players[0].getname(), 4, 1);
    graph->placeNewArmies(players[0].getname(), 4, 1);
    graph->placeNewArmies(players[0].getname(), 4, 2);
    graph->placeNewArmies(players[1].getname(), 4, 2);
    graph->placeNewArmies(players[1].getname(), 4, 3);
    printGraph(graph);*/
    // cout << "\n1.--------------------------------"<<players[0].computeScore();
    // cout << "\n2.-------------------------------- " << players[1].computeScore(); 

    return 0;
}