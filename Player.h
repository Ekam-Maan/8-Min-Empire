#include "Map.h"
#include "Cards.h"

#pragma once

class Player
{
    private:
        string playerName;
        int money;
        int noOfDisks;
        int armies;

    public:
        static int startingRegion;
        Graph *graph;
        Hand *hand;
        
        typedef pair<int, int> valueVertex;
        typedef pair<string,int> valueHandList;
        vector<valueHandList> *handList;
        vector<valueVertex> *cityList;
        vector<valueVertex> *armyList;

        pair<int, int>* NoOfArmiesInCountry(int country);
        pair<int, int>* NoOfCitiesInCountry(int country);
        Player();
        Player(Graph *graph, string playerName, int diskNum, int playerNum, int armyNum, Hand *hand);
        bool PayCoin(int coins);
        bool PLaceNewArmies(int armiesNum, int country);
        bool MoveArmies(int armiesNum, int src, int des);
        bool MoveOverLand(int armiesNum, int src, int des);
        bool BuildCity(int country);
        bool DestroyArmy(int country);
        void display();
        void displayCards();
        void pickCard();

        string getname(){ return playerName; }
        void setname(string name){ playerName = name; }

        int getmoney(){ return money; }
        void setmoney(int m){ money = m; }

        int getdisks() { return noOfDisks; }
        void setdisks(int d) { noOfDisks = d; }

        int getarmies() { return armies; }
        void setarmies(int a) { armies = a; }
};
