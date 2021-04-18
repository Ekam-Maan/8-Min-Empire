#include "biddingfacility.h"
#include <iostream>
#include <list>

using namespace std;

biddingfacility::biddingfacility()
{
    winningbid = 0;
}

biddingfacility::biddingfacility(biddingfacility* obj)
{
    winningbid = obj->winningbid;
}

biddingfacility biddingfacility::operator = (biddingfacility* obj)
{
    if ( obj != this )
        winningbid = obj->winningbid;
    
    return *this;
}

ostream& operator << (ostream& out, biddingfacility* obj)
{
    out<<"\nWinning bid: "<<obj->winningbid;
    return out;
}


//Returns true if player one has won and false if player two has won

bool biddingfacility::bid( Player* one, Player* two )
{   
    int bidamountone = 0;    //Bid amount of each player
    int bidamounttwo = 0;
    bool playerone_won = true;

    //Each player enters a bid val
    cout<<one->getname()<<" enter bidding amount: ";
    cin>>bidamountone;

    while ( bidamountone > one->getmoney() )
    {
        cout<<"You donot have enough money. Please enter again: ";
        cin>>bidamountone;
    }  


    cout << two->getname() << " enter bidding amount: ";
    cin >> bidamounttwo;

    while (bidamounttwo > two->getmoney())
    {
        cout << "You donot have enough money. Please enter again: ";
        cin >> bidamounttwo;
    }


    //--------------------Deciding winning bid and player--------------------------
    if (bidamountone > bidamounttwo)
        playerone_won = true;
   

    if (bidamounttwo > bidamountone)
        playerone_won = false;
   

    //Two players have same bid amount then compare and return their lastname
    //if lastname of player one is smaller he will go first and hence return true 
    else if(bidamountone== bidamounttwo)
    {
        string lastnameone = one->getname().substr( one->getname().find(" ") );
        string lastnametwo = two->getname().substr( two->getname().find(" "));

        if ( lastnameone < lastnametwo )
            playerone_won = true;
      

        else if (lastnametwo < lastnameone)
            playerone_won = false;
    }

    if (playerone_won)
    {
        cout << "\n\n\n" << one->getname() << " has Won the Bid\n";
        one->PayCoin(bidamountone);
    }

    else
    {
        cout << "\n\n\n" << two->getname() << " has Won the Bid\n";
        two->PayCoin(bidamounttwo);
    }

    return playerone_won;
}
