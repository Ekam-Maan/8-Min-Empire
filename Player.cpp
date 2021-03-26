#include <iostream>
#include "Player.h"


int Player::startingRegion = 0;

Player::Player(){}

Player:: Player(Graph *graph, string Name, int diskNum, int tokenNum, int armyNum,Hand *hand)
{
    noOfDisks = diskNum;
    money = tokenNum;
    armies = armyNum;
    playerName = Name;
    VP = 0;
    Crystals = 0;

    this->graph = graph;
    this->hand=hand;

    cityList = new vector<valueVertex>;

    for (int i = 0; i < graph->V; i++) 
    {
        cityList->push_back(make_pair(i, 0));
    }

    armyList = new vector<valueVertex>;

    for (int i = 0; i < graph->V; i++)
    {
        armyList->push_back(make_pair(i, 0));
    }

    handList = new vector<valueHandList>;

    valueVertex* armyIn = NoOfArmiesInCountry(startingRegion);
    armies = armies - 4;
    armyIn->second = armyIn->second + 4;
   // cout << "Successfully added the 4 armies to the startingRegion\n";
}

void Player :: display()
{
    cout << "\n** " << playerName << " **" << endl;
    cout << "No of Disks of the player: " << getdisks() << endl;
    cout << "Amount of Money of the player: " << getmoney() << endl;
    cout << "No of armies of the player: " << getarmies() << endl;
    cout << "\nArmies of the player \t";

    vector<valueVertex>::iterator index;
    for (index = (armyList)->begin(); index !=(armyList)->end(); ++index) 
        cout << "\t" << (index->first) << ": " << index->second;
    

    cout << "\nCities of the player:\t";
   // vector<valueVertex>::iterator index;
    for (index = (cityList)->begin(); index !=(cityList)->end(); ++index) 
        cout << "\t" << (index->first) << ": " << index->second;


    displayCards();
    
    cout << "\n\n" << endl;

}

void Player :: pickCard()
{
    int cost, index = -1;

    hand->Show();

    while (index > 6 || index < 1)
    {
        cout << "\nEnter Index to Buy card (1-Index): "; cin >> index;
    }

    --index;    //To make it 0-index

    cost = hand->getCardCost(index);

    while (!PayCoin(cost))
    {
        cout << "\nYou donot have enough money, pick another card";
        cout << "\nEnter Index to Buy card: "; cin >> index;
        --index;
        cost = hand->getCardCost(index);
    }

    Card card = hand->exchange(index);
    cout << "\nCard action: "<<card.action;

    performgood(card.good);

    handList->push_back(make_pair(card.toString(),0));
}


void Player:: displayCards()
{
    cout<<"\nCards list:";
    vector<valueHandList>::iterator j;
    for (j = (handList)->begin(); j !=(handList)->end(); ++j) {
            cout<<"\n"<<(j->first);
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
        
        if (cityIn->first == vertex) 
        {
            if (cityIn->second <= 0 && vertex != startingRegion)
            {
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

 void Player::computeScore() {

    int maxArmies = 0;
    int vp = 0;

    for (int i = 0; i < graph->V; i++) {

        if (graph->arr[i].t->getOwner() == playerName) {   // cheking winner of a region
            vp++;
            cout << "\n " << i << "vp++ region ;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
        }
    }
    for (int i = 0; i < graph->cont; i++)
    {   
        unordered_map<string, int> ownerlist;
        for (int j = 0; j < graph->V; j++) {
            
            if (graph->arr[j].t->getCID() == i) {
                string owner = graph->arr[j].t->getOwner();
                ownerlist[owner] ++;
                
            }
        }
        int max = 0;
        unordered_map<string, int>::iterator itr = ownerlist.begin();
        
        bool tie = false;
        for (itr = (ownerlist).begin(); itr != (ownerlist).end(); ++itr) {
            if (itr->second > max) {
                max = itr->second;
                tie = false;
            }
            if (itr->second == max) {
                tie = true;
            }
        }
        if(tie){}
        else if(ownerlist[playerName] == max) {
            vp++;
        }
        
    }
    VP = vp;
    
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



void Player::performgood(string good)
{
    if (good == "VP Point")
        setVP( getVP() + 1 );

    else if (good.find("Crystal") != string::npos)
    {
        if (good.find("X") != string::npos)
        {
            int index = good.find("X");
            int num = std::stoi( good.substr(0,index) );
            setCrystals(getCrystals() + num);
        }

        else
        {
            setCrystals( getCrystals() + 1 );
        }
    }

    else if (good.find("Coin") != string::npos)
    {
        if (good.find("X") != string::npos)
        {
            int index = good.find("X");
            int num = std::stoi(good.substr(0, index));
            setmoney(getmoney() + num);
        }

        else
        {
            setmoney(getmoney() + 1);
        }
    }

}