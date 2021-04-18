#include <iostream>
#include "Player.h"

int Player::startingRegion = 1;

//Default constructor
Player::Player()
{
    noOfDisks = 3;
    money = 14;
    armies = 18;
    playerName = "NO-NAME";
    VP = 0;
    Crystals = 0;
    controlledRegions = 0;

    strategy = new HumanStrategy();
    graph = NULL;
    hand = NULL;
    cityList = NULL;
    handList = NULL;
    armyList = NULL;
}

//Parameterized Constructor
Player:: Player(Graph *graph, string Name, int diskNum, int tokenNum, int armyNum,Hand *hand)
{
    noOfDisks = diskNum;
    money = tokenNum;
    armies = armyNum;
    playerName = Name;
    VP = 0;
    Crystals = 0;
    controlledRegions = 0;
    strategy = new HumanStrategy();

    this->graph = graph;
    this->hand = hand;

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
    graph->placeNewArmies(getname(),4,startingRegion);
}


Player::Player(Player* obj)
{
    noOfDisks = obj->getdisks();
    money = obj->getmoney();
    armies = obj->getarmies();
    playerName = obj->getname();
    VP = obj->getVP();
    Crystals = obj->getCrystals();
    controlledRegions = 0;

    strategy = new HumanStrategy();
    graph = obj->graph;
    hand = obj->hand;

    cityList = new vector<valueVertex>;
    armyList = new vector<valueVertex>;
    handList = new vector<valueHandList>;

    vector<valueVertex>::iterator index;

    for (index = (obj->armyList)->begin(); index != (obj->armyList)->end(); ++index)
        armyList->push_back(make_pair(index->first, index->second));

    for (index = (obj->cityList)->begin(); index != (obj->cityList)->end(); ++index)
        cityList->push_back(make_pair(index->first, index->second));

    vector<valueHandList>::iterator index2;

    for (index2 = (obj->handList)->begin(); index2 != (obj->handList)->end(); ++index)
        handList->push_back(make_pair(index2->first, index2->second));
}


void Player::setStrategy() {
   
    cout << "\n\nEnter 1 for Human Strategy.\n";
    cout << "\nEnter 2 for Greedy Strategy.\n";
    cout << "\nEnter 3 for Moderate Strategy.\n";
    cout << "\n please enter your choice here: ";
    cin >> Strategychoice;

    if (Strategychoice == 1)
    {
        delete strategy;
        strategy = new HumanStrategy();
    }

    else if (Strategychoice == 2)
    {
        delete strategy;
        strategy = new GreedyStrategy();
    }

    else if (Strategychoice == 3 )
    {
        delete strategy;
        strategy = new ModerateStrategy();
    }

    else {
        cout << "You did not enter a valid choice. ";
    }
    
}

void Player::executeStrategy(Player* otherPlayer) {
    strategy->execute(this, otherPlayer);
}

void Player :: display()
{
    cout << "\n** " << playerName << " **" << endl;
    cout << "No of Disks of the player: " << getdisks() << endl;
    cout << "Amount of Money of the player: " << getmoney() << endl;
    cout << "No of armies of the player: " << getarmies() << endl;
    
    cout << "\nNo of controlledRegions of the player: " << getcontrolledRegions() << endl;
    cout << "Crystals of the player: " << getCrystals() << endl;
    cout << "Victory Points of the player: " << getVP() << endl;

    
    vector<valueVertex>::iterator index;

    cout << "\nArmies of the player \t";
    for (index = (armyList)->begin(); index !=(armyList)->end(); ++index) 
        cout << "    " << (index->first) << ": " << index->second;
    

    cout << "\nCities of the player:\t";
    for (index = (cityList)->begin(); index !=(cityList)->end(); ++index) 
        cout << "    " << (index->first) << ": " << index->second;


    displayCards();
    
    cout << "\n\n\n" << endl;

}

Card Player :: pickCard()
{
    //PHASE-OBSERVER
    notify("turn");

    int cost, index = -1;
    hand->Show();

    while (index > 6 || index < 1)
    {
        cout << "\nEnter Index to Buy card (1-Index): ";
        cin >> index;
    }

    cost = hand->getCardCost(index - 1);         //To make it 0-index

    while (!PayCoin(cost))
    {
        //PHASE-OBSERVER
        notify("Not enough money");

        cout << "\nEnter Index to Buy card: "; cin >> index;
        cost = hand->getCardCost(index - 1);
    }

    Card card = hand->exchange(index - 1);
    handList->push_back(make_pair(card.toString(), index));
    setlastCard(card);

    //PHASE-OBSERVER
    notify("cardpicked");
    
    return card;
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
            cout<<getname()<<" doesn't have enough money to pay.";
            return false;
    }
    else
    {
            cout<<"Payment Successfull. "+getname()+" payed: "<<coins;
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

        graph->placeNewArmies(getname(),armiesNum,vertex);

        cout<<"Successfully added the armies";
   
        return true;
     }
    

}
bool Player :: MoveArmies(int armiesNum, int src, int des)
{
    valueVertex *armyTo = NoOfArmiesInCountry(des);
    valueVertex *armyFrom = NoOfArmiesInCountry(src);

    if (armyFrom->second < armiesNum) 
    {
        cout << "Cant move the armies. Not enough amrmies available" << endl;
        return false; 
    } 
    else 
    {
        armyTo->second= armyTo->second + armiesNum;
        armyFrom->second= armyFrom->second - armiesNum;

        graph->moveArmies(getname(),armiesNum,src,des);

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

 
    bool checkLand = isLandConn(graph, src, des);
    if(checkLand == false)
    {
        cout << "You can only move from " << src << " to " << des << " by water." << endl;
        return false;
    }        
    
    return MoveArmies(armiesNum, src, des);
}


bool Player::MoveOverWater(int armiesNum, int src, int des)
{
    bool adjacency = isAdj(graph, src, des);
    if (adjacency == false)
    {
        cout << src << " and " << des << " are not adjacent." << endl;
        return false;
    }

    else if (adjacency == true)
    {
        bool checkLand = isLandConn(graph, src, des);
        if (checkLand == true)
        {
            cout << "You can only move from " << src << " to " << des << " by Land." << endl;
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
        graph->destroyArmy(getname(),-1,vertex);
        return true;
    }
    else 
    {
        cout << "Army cannot be destroyed, not enough armies" << endl;
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

            graph->buildCity(getname(),country);
            
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


void Player::performaction(string action, Player* otherPlayer)
{
    cout << "\nCard action: " << action;

    if (Strategychoice == 1)
    {
        char ans = 'y';
        cout << "\n\nDo you want to ignore the action (y|n)?: "; cin >> ans;

        if (ans == 'y')
            return;
    }

    if (action.find("AND") != string::npos)
    {
        string actionone = action.substr(0, action.find("AND") - 1);
        string actiontwo = action.substr(action.find("AND") + 4);

        performaction(actionone,otherPlayer);
        performaction(actiontwo,otherPlayer);
        return;
    }


    else if (action.find("OR") != string::npos)
    {
        string actionone = action.substr(0, action.find("OR") - 1);
        string actiontwo = action.substr(action.find("OR") + 3);

        int num = 1;
        cout << "Enter which action you want to perform (1 or 2): ";
        cin >> num;

        if ( num == 1 )
            performaction(actionone, otherPlayer);
        
        else 
            performaction(actiontwo, otherPlayer);
        
        return;
    }


    else if ( action.find("Place new armies") != string::npos )
    {
        int numOfarmies = stoi(action.substr(0,1));
        int vertex = -1;
        
        while (vertex < 0 || vertex >= graph->V)
        {
            cout << "Enter vertex: "; cin >> vertex;
        }

        bool res = PLaceNewArmies(numOfarmies, vertex);

        if (!res)     //action failed, redo
            performaction(action,otherPlayer);
    }



    else if ( action.find("Move armies") != string::npos )
    {
        int numOfarmies = stoi(action.substr(0,1));
        int src = -1;
        int dest = -1;

        while (src < 0 || src >= graph->V)
        {
            cout << "Enter source vertex: "; cin >> src;
        }

        while (dest < 0 || dest >= graph->V)
        {
            cout << "Enter destination vertex: "; cin >> dest;
        }

        bool res = MoveOverLand(numOfarmies, src, dest);

        if (!res)     //action failed, redo
            performaction(action, otherPlayer);
    }


    else if (action.find("Move over land/water") != string::npos)
    {
        int numOfarmies = stoi(action.substr(0, 1));
        int src = -1;
        int dest = -1;
        int num = 1;
        bool res = true;


        cout << "Enter which action you want to perform (1-Move over Land or 2-Move our Water)";
        cout << "\nRemember moving over water takes 3 movement speed: ";
        cin >> num;


        while (src < 0 || src >= graph->V)
        {
            cout << "Enter source vertex: "; cin >> src;
        }

        while (dest < 0 || dest >= graph->V)
        {
            cout << "Enter destination vertex: "; cin >> dest;
        } 

        if ( num == 1 )
            res = MoveOverLand(numOfarmies, src, dest);

        else
            res = MoveOverWater(numOfarmies/3, src, dest);

        if (!res)     //action failed, redo
            performaction(action, otherPlayer);
    }




    else if (action.find("Build City") != string::npos)
    {
        int numOfarmies = -1;
        int vertex = -1;

        while (vertex < 0 || vertex >= graph->V)
        {
            cout << "Enter vertex where to build city: "; cin >> vertex;
        }


        bool res = BuildCity(vertex);

        if (!res)     //action failed, redo
            performaction(action, otherPlayer);
    }




    else if (action.find("Destroy army") != string::npos)
    {
        int numOfarmiesInVertex = 0;
        int src = -1;


        while ( numOfarmiesInVertex <= 0 )
        {
            cout << "Enter vertex where to destroy army: "; cin >> src;

            if (src < 0 || src >= graph->V)
            {
                cout << "Enter valid vertex\n";
                continue;
            }

            valueVertex* armyIn = NoOfArmiesInCountry(src);
            numOfarmiesInVertex = armyIn->second;
            
            if (numOfarmiesInVertex <= 0)
                cout << "You dont have enough armies there\n";
        }


        bool res = otherPlayer->DestroyArmy(src);

        if (!res)     //action failed, redo
            performaction(action, otherPlayer);
    }
}

int Player::computeScore() {

    int maxArmies = 0;
    int vp = 0;

    for (int i = 0; i < graph->V; i++) 
    {
        if (graph->arr[i].t->getOwner() == playerName)
        {  
            ++vp;
            ++controlledRegions;
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
        if (tie) {}
        
        else if (ownerlist[playerName] == max) 
            vp++;
    }
    VP += vp;

    return VP;
}


//Donot delete hand and graph since they are shared between all players
//They will be deleted by the game class
Player::~Player()
{
    cout << "\n\n\n\nPLAYER DESRUCTOR";
    delete strategy;
    delete armyList;
    delete cityList;
    delete handList;

    strategy = NULL;
    armyList = NULL;
    cityList = NULL;
    handList = NULL;
}

//Assignment operator

Player Player::operator = (Player* obj)
{
    if (obj != this)
    {
        delete strategy;
        delete armyList;
        delete cityList;
        delete handList;

        strategy = NULL;
        armyList = NULL;
        cityList = NULL;
        handList = NULL;

        noOfDisks = obj->getdisks();
        money = obj->getmoney();
        armies = obj->getarmies();
        playerName = obj->getname();
        VP = obj->getVP();
        Crystals = obj->getCrystals();

        graph = obj->graph;
        hand = obj->hand;

        cityList = new vector<valueVertex>;
        armyList = new vector<valueVertex>;
        handList = new vector<valueHandList>;

        vector<valueVertex>::iterator index;

        for (index = (obj->armyList)->begin(); index != (obj->armyList)->end(); ++index)
            armyList->push_back(make_pair(index->first, index->second));

        for (index = (obj->cityList)->begin(); index != (obj->cityList)->end(); ++index)
            cityList->push_back(make_pair(index->first, index->second));

        vector<valueHandList>::iterator index2;

        for (index2 = (obj->handList)->begin(); index2 != (obj->handList)->end(); ++index)
            handList->push_back(make_pair(index2->first, index2->second));
    }

    return *this;
}


//Overloaded stream insertion and output operaters;

ostream& operator << (ostream& out, Player& obj)
{
    out << "\n** " << obj.playerName << " **" << endl;
    out << "No of Disks of the player: " << obj.getdisks() << endl;
    out << "Amount of Money of the player: " << obj.getmoney() << endl;
    out << "No of armies of the player: " << obj.getarmies() << endl;
    out << "\nArmies of the player \t";


    vector<Player::valueVertex>::iterator index;
    for (index = (obj.armyList)->begin(); index != (obj.armyList)->end(); ++index)
        out << "\t" << (index->first) << ": " << index->second;


    cout << "\nCities of the player:\t";

    for (index = (obj.cityList)->begin(); index != (obj.cityList)->end(); ++index)
        out << "\t" << (index->first) << ": " << index->second;


    return out;
}


istream& operator >> (istream& in, Player& obj)
{
    in>>obj.noOfDisks;
    in>>obj.money;
    in>>obj.armies;
    in>>obj.playerName;

    return in;
}



//Getter-setter
string Player::getname() { return playerName; }
void Player::setname(string name) { playerName = name; }

int Player::getmoney() { return money; }
void Player::setmoney(int m) { money = m; }

int Player::getdisks() { return noOfDisks; }
void Player::setdisks(int d) { noOfDisks = d; }

int Player::getarmies() { return armies; }
void Player::setarmies(int a) { armies = a; }

int Player::getVP() { return VP; }
void Player::setVP(int a) { VP = a; }

int Player::getCrystals() { return Crystals; }
void Player::setCrystals(int a) { Crystals = a; }

int Player::getcontrolledRegions() { return controlledRegions; }
void Player::setcontrolledRegions(int a) { controlledRegions = a; }

Card Player::getlastCard() { return lastCard; }
void Player::setlastCard(Card card) { lastCard = card; }