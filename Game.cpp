#include "Game.h"
#include <iostream>

Game::Game()
{
    cout << "Welcome to 8-min-empire legends\n";

    stash = 0;

    graph = MapLoader::loadBoard();

    //graph->placeNewArmies("SPD",0,0);

    cout << "\n\nCreating Deck and drawing 6 cards\n\n";
    hand = new Hand();
    hand->Show();

    cout << "Enter number of Players: "; cin >> numOfPlayers;
    cout << "\n";
    cin.ignore(1, '\n');

    players = new Player[numOfPlayers];

    for (int i = 0; i < numOfPlayers; ++i)
    {
        string name;
        cout << "Enter Player " << i + 1 << " name: ";
        getline(cin, name);

        players[i] = Player(graph, name, 3, 14, 18, hand);
    }

    cout << "\n\nDisplaying PlayerList\n";
    cout << "\n--------------------------------------------------\n";
    
    for (int i = 0; i < numOfPlayers; ++i) {
       players[i].display();
      /*  graph->placeNewArmies(players[i].getname(), 4, 0);
        printGraph(graph);
        graph->moveArmies(players[i].getname(), 2, 0, 1);
        printGraph(graph);*/
    }
        

    //---------------------Bidding---------------------
    bidfac = new biddingfacility();
    Queue = bidfac->bid(players, numOfPlayers);

    cout << "\nPlayer's Queue\n";
    cout << "--------------------------------------------------\n";

    showQ();
}

void Game::showQ()
{
    for (int i = 0; i < numOfPlayers; ++i)
    {
        Player p = Queue.front();
        cout << p.getname() << "     ";
        Queue.pop();
        Queue.push(p);
    }
    cout << endl;
}

void Game::loop()
{
    cout << "\n\nStarting Game Loop";
    cout << "\n--------------------------------------------------\n";
    int brk = 0;
    Player* temp = nullptr;

    while (true)
    {
        temp = &Queue.front();
        cout << "\n"<<temp->getname()<<"'s turn\n\n";

        temp->pickCard();
        //temp->displayCards();

        Queue.push(*temp);
        Queue.pop();

        ++brk;
        if (brk == 5)
            break;

        temp = nullptr;
    }
    

}

Game::~Game()
{
    cout << "\nCalling Game destruction";

    delete[] players;
    delete hand;
    delete graph;
    delete bidfac;
}