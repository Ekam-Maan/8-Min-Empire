#include <iostream>
#include "Player.h"
#include "../Part1/Map.h"



Player:: Player(Graph *graph, string Name, int diskNum, int tokenNum, int armyNum )
{
    disks = new int(diskNum);
    tokens = new int(tokenNum);
    armies = new int(armyNum);
    name = new string(Name);
    this->graph = graph;
    citiesIn = new vector<countryValue>;
    for (int i =0;i<4;i++) 
    {
        citiesIn->push_back(make_pair(i, 0));
    }

    armiesIn = new vector<countryValue>;
    for (int i=0;i<4;i++) {
        armiesIn->push_back(make_pair(i, 0));
    }

}
void Player :: display()
{
    cout << "\n----------- " << *name << " ---------------------------------" << endl;
    cout << left <<  setw(10) << "Disks: " << *disks << endl;
    cout << left <<  setw(10) << "Tokens: " << *tokens << endl;
    cout << left <<  setw(10) << "Armies: " << *armies << endl;
    cout << "\nArmies in:\t";
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        cout << "\t" << (i->first) << ": " << i->second;
    }
    cout << "\nCities in:\t";
    vector<countryValue>::iterator t;
    for (t = (citiesIn)->begin(); t !=(citiesIn)->end(); ++t) {
        cout << "\t" << (t->first) << ": " << t->second;
    }
    cout << "\n\n" << endl;
    
}
bool Player :: PayCoin(int coins)
{
      if(*tokens<coins){
        cout << "Player cannot afford that many coins." << endl;
        return false;
    }
    else{
        cout << "Player payed." << endl;
        *tokens-=coins;
        return true;
    }
}
bool Player :: PLaceNewArmies(int armiesNum, int country)
{
    int startingRegion = 1;
     if (*armies < armiesNum) 
     {
            cout << "Player does not have enough armies to place." << endl;
            return false;
    }
    countryValue *cityIn = getCitiesInCountry(country);
        
    if (cityIn->first == country) {
            if (cityIn->second <= 0 && country != startingRegion) {
                cout << "Player does not have cities in that country. Cannot place armies." << endl;
                return false;
            }
        }

    countryValue *armyIn = getArmiesInCountry(country);
        *armies -= armiesNum;
        armyIn->second = armyIn->second + armiesNum;
        cout<<"Successfully added the armies";


}
bool Player :: MoveArmies(int armiesNum, int src, int des)
{
     countryValue *armyInTo = getArmiesInCountry(des);
    countryValue *armyInFrom = getArmiesInCountry(src);

    if (isAdj(graph,des,src)==false) {
        cout << src << " and " << des << " are not adjacent." << endl;
        return false;
    }

    if (armyInFrom->second < armiesNum) {
        cout << "Not enough armies to move." << endl;
        return false; //there are not enough to country to move
    } else {
        armyInTo->second+= armiesNum;
        armyInFrom->second-=armiesNum;
        cout << "Moved " << armiesNum << " armies from " << src << " to " << des << endl;
        return true;
    }


}
bool Player :: MoveOverLand(int armiesNum, int src, int des)
{
    bool adjacency = isAdj(graph,src,des);
    if (adjacency == false) {
        cout << src << " and " << des << " are not adjacent." << endl;
        return false;
    }
    if (adjacency == true) {
        cout << "You can only move from " << src << " to " << des << " by water." << endl;
        return false;
    }

    return MoveArmies(armiesNum, src, des);
}
bool Player :: DestroyArmy(int country)
{
    countryValue *armyIn = getArmiesInCountry(country);

    if (armyIn->second > 0) {
        cout << "Destroyed army of " << *(name) << " in " << country << endl;
        *armies+=1;
        armyIn->second--;
        return true;
    }

    else {
        cout << "Cannot destroy army" << endl;
    }

    return false;
}
bool Player:: BuildCity(int country)
{
     if(*disks < 1) {
        cout << "Not enough disks." << endl;
        return false;
    }

    countryValue *armyIn = getArmiesInCountry(country);

    if (armyIn->second > 0) {
        *disks-=1;
        countryValue *cityIn = getCitiesInCountry(country);
        cityIn->second++;
        cout << "Built a city in " << country << endl;
        return true;
    }

    else {
        cout << "Cannot build a city where player has no armies." << endl;
    }

    return false;
}
 


pair<int, int>* Player::getArmiesInCountry(int country) {
    vector<countryValue>::iterator i;
    for (i = (armiesIn)->begin(); i !=(armiesIn)->end(); ++i) {
        if (i->first == country) {
            return &(*i);
        }
    }
}

pair<int, int>* Player::getCitiesInCountry(int country) {
    vector<countryValue>::iterator i;
    for (i = (citiesIn)->begin(); i !=(citiesIn)->end(); ++i) {
        if (i->first == country) {
            return &(*i);
        }
    }
}