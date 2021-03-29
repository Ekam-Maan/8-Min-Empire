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

    cin.ignore(1, '\n');
    string name;

    cout << "Enter Player one's name: ";
    getline(cin, name);
    one = new Player(graph, name, 3, 14, 18, hand);



    cout << "Enter Player two's name: ";
    getline(cin, name);
    two = new Player(graph, name, 3, 14, 18, hand);


    cout << "\n\n\nDisplaying PlayerList\n";
    cout << "\n--------------------------------------------------\n";
    one->display();
    two->display();

  
    //---------------------Bidding---------------------
    bidfac = new biddingfacility();
    playerone_turn = bidfac->bid(one, two);

    //Get the biddingamount by subtracting inital number of coins to current and update the stash
    if (playerone_turn)
        setstash( getstash() + (14 - one->getmoney()) );

    else
        setstash(getstash() + (14 - two->getmoney()));
}


void Game::loop()
{
    cout << "\n\nStarting Game Loop";
    cout << "\n--------------------------------------------------\n";
    int ctr = 0;
    string action = "";
    
    //Since there are players and each player picks one card during a turn
    //Game will stop when each player has 13 cards or a total of 26 turns have finished
    while (ctr < 26)
    {
        if (playerone_turn)
        {
            cout << "\n\n\n" << one->getname() << "'s turn\n\n";
            action = one->pickCard();
            one->performaction(action,two);
            one->display();
        }

        else
        {
            cout << "\n\n\n" << two->getname() << "'s turn\n\n";
            action = two->pickCard();
            two->performaction(action,one);
            two->display();
        }

        if (ctr == 3)
            break;
        
        playerone_turn = !playerone_turn;
        ++ctr;
    }
    

}


//Player having max num of Crystals receives 2 VP points
//If its a tie, no one receives any points
void Game::DecideWinner()
{   
    cout << "\n\n\n Game Ended. Deciding Winner\n\n\n";
    one->display();
    two->display();

    int Crystalsone = one->getCrystals();
    int Crystalstwo = two->getCrystals();

    if ( Crystalsone > Crystalstwo )
        one->setVP( one->getVP() + 2 );
    
    else if (Crystalstwo > Crystalsone)
        two->setVP(two->getVP() + 2);

    else if ( Crystalsone == Crystalstwo )
    {
        one->setVP(one->getVP() + 1);
        two->setVP(two->getVP() + 1);
    }


    //--------------Deciding Winner-------------------------
    Player *Winner = one;  
    int VPone = one->getVP();
    int VPtwo = two->getVP();

    if ( VPone > VPtwo )
        Winner = one;
    
    else if ( VPtwo > VPone )
        Winner = two;

    //Having equal VP
    else if ( VPone == VPtwo )
    {
        if ( one->getmoney() > two->getmoney()  )
            Winner = one;

        else if ( two->getmoney() > one->getmoney() )
            Winner = two;
     
       //Having same money
        else if ( one->getmoney() == two->getmoney())
        {
            //Having lesser armies offboard meaning more armies are on the board
            if ( one->getarmies() < two->getarmies() )
                Winner = one;

            if ( two->getarmies() < one->getarmies())
                Winner = two;

            //Having equal armies
            else if ( one->getarmies() == two->getarmies() )
            {
                if ( one->getcontrolledRegions() > two->getcontrolledRegions() )
                    Winner = one;

                else if ( two->getcontrolledRegions() > one->getcontrolledRegions() )
                    Winner = two;
            }
        }
    }
    
   
    cout << "\n\n---------------------------------------------------------------\n\n";
    cout << Winner->getname() << " has won the game";
    cout << "\n\n---------------------------------------------------------------\n\n";

    //delete Winner;
    Winner = NULL;
}

Game::~Game()
{
    cout << "\nCalling Game destruction";

    delete one;
    delete two;
    delete hand;
    delete graph;
    delete bidfac;
}


//Getter-Setter

int Game::getstash() { return stash; }
void Game::setstash(int num) { stash = num; }