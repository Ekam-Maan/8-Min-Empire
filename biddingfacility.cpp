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
    winningbid = obj->winningbid;
    return *this;
}

ostream& operator << (ostream& out, biddingfacility* obj)
{
    out<<"\nWinning bid: "<<obj->winningbid;
    return out;
}


queue<Player> biddingfacility::bid( Player* players, int size )
{   
    queue<Player> q;
    list<string> List;      //list of players having max bid, can be multiple if tie
    int bidamount;    //Bid amount of each player
    int maxbid = 0;         //curr max bid

    //Each player enters a bid val
    //if it is max bid, the list containing player having max bid till now is cleared
    //if it is equal to max bid, player is added to the list
    for ( int i = 0; i < size; ++i )
    {
        cout<<players[i].getname()<<" enter bidding amount: ";
        cin>>bidamount;

        while ( bidamount > players[i].getmoney() )
        {
            cout<<"You donot have enough money. Please enter again: ";
            cin>>bidamount;
        }    

        if ( bidamount > maxbid )
        {
            maxbid = bidamount;
            List.clear();
        }

        if ( bidamount == maxbid )
        {
            string lastname = players[i].getname().substr( players[i].getname().find(" ") );
            List.push_back( lastname + to_string(i));
        }
    }


    if ( List.size() != 1 )     //there is a tie
        List.sort();
       
    string winningplayer = List.front();    
    int winningIndex = winningplayer[ winningplayer.length() - 1 ] - '0';
    
    cout<<"\n"<<players[winningIndex].getname()<<" has won the bid\n";
    winningbid = maxbid;
    players[winningIndex].PayCoin( maxbid );
 
    q.push( players[winningIndex] );

    for ( int i = 0; i < size; ++i )
    {
        if ( i == winningIndex )
            continue;
        
        q.push( players[i] );
    }

    return q;
}
