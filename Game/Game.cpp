#include "Game.h"
#include <iostream>

Game::Game()
{
    stash = 0;

    graph = new Graph(4);
    hand = new Hand();
    bidfac = new biddingfacility();

    cout<<"Enter number of Players: ";cin>>numOfPlayers;
    cout<<"\n";
    cin.ignore(1,'\n');

    players = new Player[numOfPlayers];

    for ( int i = 0; i < numOfPlayers; ++i )
    {
        string name;
        cout<<"Enter Player "<<i+1<<" name: ";
        getline(cin, name);

        players[i] = Player(graph,name,3,14,18,hand);
    }

    //---------------------Bidding---------------------
    
    Queue = bidfac->bid(players,numOfPlayers);

     
}

void Game::showQ()
{
    for ( int i = 0; i < numOfPlayers; ++i )
    {
        Player p = Queue.front();   
        cout<<p.getname()<<"     ";
        Queue.pop();
        Queue.push(p);
    }
    cout<<endl;
}

Game::~Game()
{
    cout<<"\nCalling Game destruction";

    delete [] players;
    delete hand;
    delete graph;
    delete bidfac;
}