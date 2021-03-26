#include "Game.h"
#include <iostream>

Game::Game()
{
    cout << "Welcome to 8-min-empire legends\n";

    stash = 0;

    graph = MapLoader::loadBoard();

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
    
    for (int i = 0; i < numOfPlayers; ++i)
        players[i].display();

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

        Queue.push(*temp);
        Queue.pop();

        ++brk;
        if (brk == 5)
        //if (GameEnded())
            break;

        temp = nullptr;
    }

}

bool Game::GameEnded()
{
    int minimumReqNumCards;

    if (numOfPlayers == 2)
        minimumReqNumCards = 13;

    if (numOfPlayers == 3)
        minimumReqNumCards = 10;

    if (numOfPlayers == 4)
        minimumReqNumCards = 8;

    for (int i = 0; i < numOfPlayers; ++i)
        if ((players + i)->handList->size() != minimumReqNumCards)
            return false;

    return true;
}

//Player having max num of Crystals receives 2 VP points
//If its a tie, no one receives any points
void Game::DecideWinner()
{
    int maxCrystals = 0;
    string maxCrystalowner = "";

    for (int i = 0; i < numOfPlayers; ++i)
    {
        if ((players + i)->getCrystals() > maxCrystals)
        {
            maxCrystals = (players + i)->getCrystals();
            maxCrystalowner = (players + i)->getname();
        }

        else if ((players + i)->getCrystals() == maxCrystals)
            maxCrystalowner = "";
    }

    int maxVP = 0;
    Player *Winner = (players + 0);

    for (int i = 0; i < numOfPlayers; ++i)
    {
        (players + i)->display();
        //int VP = (players + i)->ComputeScore();
        int VP = 0;

        if ((players + i)->getname() == maxCrystalowner)
            VP += 2;

        if (VP > maxVP)
        {
            maxVP = VP;
            Winner = (players + i);
            continue;
        }

        if (VP == maxVP)
        {
            if ( (players + i)->getmoney() > Winner->getmoney()  )
                Winner = (players + i);
     
            //Having lesser armies meaning more armies are on the board
            else if ((players + i)->getmoney() == Winner->getmoney())
            {
                if ((players + i)->getarmies() < Winner->getarmies())
                    Winner = (players + i);
            }
        }
    }


    cout << "\n\n---------------------------------------------------------------\n\n";
    cout << Winner->getname() << " has won the game";
    cout << "\n\n---------------------------------------------------------------\n\n";

    delete Winner;
    Winner = nullptr;
}

Game::~Game()
{
    cout << "\nCalling Game destruction";

    delete[] players;
    delete hand;
    delete graph;
    delete bidfac;
}