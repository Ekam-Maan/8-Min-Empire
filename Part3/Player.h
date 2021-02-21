#include "../Part1/Map.h"
#include "../Part4/Cards.h"

class Player
{

    //typedef pair<Graph*, int> countryValue;
    Graph *graph;
    
    
    
    public :
        string *name;
        int *disks;
        int *tokens;
        int *armies;
        int *age;
    
        int getTotalScore();
        typedef pair<int, int> countryValue;
        vector<Card*> *hand;
        vector<countryValue> *citiesIn;
        vector<countryValue> *armiesIn;

        pair<int, int>* getArmiesInCountry(int country);
        pair<int, int>* getCitiesInCountry(int country);
        Player(Graph *graph, string playerName, int diskNum, int tokenNum, int armyNum);
        bool PayCoin(int coins);
        bool PLaceNewArmies(int armiesNum, int country);
        bool MoveArmies(int armiesNum, int src, int des);
        bool MoveOverLand(int armiesNum, int src, int des);
        bool BuildCity(int country);
        bool DestroyArmy(int country);
        void display();

};