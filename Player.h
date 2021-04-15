#include "Map.h"
#include "Cards.h"
#include "GameObservers.h"

#pragma once

class Player : public Subject
{
    private:
        string playerName;
        int money;
        int noOfDisks;
        int armies;
        int VP;         //Victory Point
        int Crystals;
        int controlledRegions;

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
        Player(Player* obj);
        bool PayCoin(int coins);
        bool PLaceNewArmies(int armiesNum, int country);
        bool MoveArmies(int armiesNum, int src, int des);
        bool MoveOverLand(int armiesNum, int src, int des);
        bool MoveOverWater(int armiesNum, int src, int des);
        bool BuildCity(int country);
        bool DestroyArmy(int country);
        void display();
        void displayCards();
        Card pickCard();
        void performgood(string good); 
        void performaction(string action,Player* otherobj);
        int computeScore();
        Player operator = (Player* obj);
        friend ostream& operator << (ostream& out, Player& obj);
        friend istream& operator >> (istream& in, Player& obj);
        ~Player();

        string getname();
        void setname(string name);

        int getmoney();
        void setmoney(int m);

        int getdisks();
        void setdisks(int d);

        int getarmies();
        void setarmies(int a);

        int getVP();
        void setVP(int a);

        int getCrystals();
        void setCrystals(int a);

        int getcontrolledRegions();
        void setcontrolledRegions(int a);
};

