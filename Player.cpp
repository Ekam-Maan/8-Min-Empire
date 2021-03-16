#include <iostream>
#include "Player.h"


Player::Player(){}

int Player::startingRegion = -1;

Player:: Player(Graph *graph, string Name, int diskNum, int tokenNum, int armyNum,Hand *hand)
{
    noOfDisks = diskNum;
    money = tokenNum;
    armies = armyNum;
    playerName = Name;

    this->graph = graph;
    this->hand=hand;

    cityList = new vector<valueVertex>;
    for (int i =0;i<4;i++) 
    {
        cityList->push_back(make_pair(i, 0));
    }

    armyList = new vector<valueVertex>;
    for (int i=0;i<4;i++) {
        armyList->push_back(make_pair(i, 0));
    }
    startingRegion = 1;
    handList = new vector<valueHandList>;
}

void Player :: display()
{
    cout << "\n** " << getname() << " **" << endl;
    cout << "No of Disks of the player: " << getdisks() << endl;
    cout << "Amount of Money of the player: " << getmoney() << endl;
    cout << "No of armies of the player: " << getarmies() << endl;
    cout << "\nArmies of the player \t";

    vector<valueVertex>::iterator index;
    for (index = (armyList)->begin(); index !=(armyList)->end(); ++index) {
        cout << "\t" << (index->first) << ": " << index->second;
    }
    cout << "\nCities of the player:\t";
   // vector<valueVertex>::iterator index;
    for (index = (cityList)->begin(); index !=(cityList)->end(); ++index) {
        cout << "\t" << (index->first) << ": " << index->second;
    }
    cout << "\n\n" << endl;

}

void Player :: pickCard()
{
    hand->Show();
    Card card = hand->exchange(2);
    handList->push_back(make_pair(card.toString(),0));
    PayCoin(2);
    hand->Show();
}


void Player:: displayCards()
{
    cout<<"Cards list:";
    vector<valueHandList>::iterator j;
    for (j = (handList)->begin(); j !=(handList)->end(); ++j) {
            cout<<(j->first);
    }
}

bool Player :: PayCoin(int coins)
{
    if(getmoney()<coins)
    {
            cout << "The player doesn't have enough money to pay." << endl;
            return false;
    }
    else
    {
            cout << "Payment Successfull. Player payed: " <<coins<< endl;
            setmoney( getmoney()-coins );
            return true;
    }
}

bool Player :: PLaceNewArmies(int armiesNum, int vertex)
{
    
     if (getarmies() < armiesNum) 
     {
            cout << "The player doesn't have armies to move." << endl;
            return false;
     }
     else
     {
        valueVertex *cityIn = NoOfCitiesInCountry(vertex);
        
        if (cityIn->first == vertex) {
            if (cityIn->second <= 0 && vertex != startingRegion) {
                cout << "Player does not have cities in that country.  Cant add armies" << endl;
                return false;
            }
        }

        valueVertex *armyIn = NoOfArmiesInCountry(vertex);
        armies = armies - armiesNum;
        armyIn->second = armyIn->second + armiesNum;
        cout<<"Successfully added the armies";
        return true;
     }
    

}
bool Player :: MoveArmies(int armiesNum, int src, int des)
{
    valueVertex *armyTo = NoOfArmiesInCountry(des);
    valueVertex *armyFrom = NoOfArmiesInCountry(src);

    if (isAdj(graph,des,src)==false) 
    {
        cout << src << " and " << des << " are not adjacent." << endl;
        return false;
    }

    else if (armyFrom->second < armiesNum) 
    {
        cout << "Cant move the armies. Not enough amrmies available" << endl;
        return false; 
    } 
    else 
    {
        armyTo->second= armyTo->second+ armiesNum;
        armyFrom->second= armyFrom->second-armiesNum;
        cout << "Succesfully moved " << armiesNum << " armies from " << src << " to " << des << endl;
        return true;
    }


}
bool Player :: MoveOverLand(int armiesNum, int src, int des)
{
    bool adjacency = isAdj(graph,src,des);
    if (adjacency == false) 
    {
        cout << src << " and " << des << " are not adjacent." << endl;
        return false;
    }

    else if(adjacency == true)
    {
        bool checkLand = isLandConn(graph, src, des);
        if(checkLand == false)
        {
            cout << "You can only move from " << src << " to " << des << " by water." << endl;
            return false;
        }        
    }
    return MoveArmies(armiesNum, src, des);
}

bool Player :: DestroyArmy(int vertex)
{
    valueVertex *armyIn = NoOfArmiesInCountry(vertex);

    if (armyIn->second > 0) {
        cout << "Successfully Destroyed army of " << getname() << " in " << vertex << endl;
        armies = armies+1;
        armyIn->second--;
        return true;
    }
    else 
    {
        cout << "Army cannot be destroyed" << endl;
        return false;
    }

}
bool Player:: BuildCity(int country)
{
    if(getdisks() < 1) 
    {
        cout << "Not enough disks available." << endl;
        return false;
    }
    else
    {
        valueVertex *armyIn = NoOfArmiesInCountry(country);

        if(armyIn->second > 0) 
        {
            noOfDisks = noOfDisks-1;
            valueVertex *cityIn = NoOfCitiesInCountry(country);
            cityIn->second++;
            cout << "Successfully built a city in " << country << endl;
            return true;
        }
        else 
        {
            cout << "Oops. Cannot build a city where player has no armies." << endl;
            return false;
        }
    
    }
    
}
 

pair<int, int>* Player::NoOfArmiesInCountry(int vertex) 
{
    vector<valueVertex>::iterator i;
    for (i = (armyList)->begin(); i !=(armyList)->end(); ++i) 
    {
        if (i->first == vertex) 
        {
            return &(*i);
        }
    }

    return &(*i);
}

pair<int, int>* Player::NoOfCitiesInCountry(int vertex) 
{
    vector<valueVertex>::iterator i;
    for (i = (cityList)->begin(); i !=(cityList)->end(); ++i) 
    {
        if (i->first == vertex) 
        {
            return &(*i);
        }
    }

    return &(*i);
}