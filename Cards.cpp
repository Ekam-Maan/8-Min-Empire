#include "Cards.h"
#include <iostream>
#include <string>
#include <queue>
#include <iomanip>   

using namespace::std;


/*Card Information*/

string titles[] = {
  "Ancient Phoenix",     "Ancient Sage",
  "Ancient Tree Spirit", "Ancient Woods",
  "Cursed Banshee",      "Cursed Gargoyles",
  "Cursed King",         "Cursed Mausoleum",
  "Cursed Tower",        "Dire Dragon",
  "Dire Eye",            "Dire Giant",
  "Dire Goblin",         "Dire Ogre",
  "Forest Elf",          "Forest Gnome",
  "Forest Pixie",        "Forest Tree Town",
  "Graveyard",           "Lake",
  "Night Hydra",         "Night Village",
  "Night Wizard",        "Noble Hills",
  "Noble Knight",        "Noble Unicorn",
  "Stronghold",          "Arcane Manticore",   
  "Arcane Sphinx",       "Arcane Temple",       
  "Mountain Dwarf",      "Mountain Treasury",
  "Castle",              "Castle 2"
};

string goods[] = {
    "Crystal",         "Coin",
    "2X Crystal",      "2X Coin",
    "3X Crystal",      "Coin",
    "4X Crystal",      "VP Point",
    "VP Point",        "VP Point",
    "VP Point",        "2X Coin",
    "Crystal",         "Coin",
    "2X Crystal",      "2X Coin",
    "3X Crystal",      "2X Crystal",
    "4X Crystal",      "2X Coin",
    "VP Point",        "VP Point",
    "VP Point",        "2X Coin",
    "Crystal",         "Coin",
    "2X Crystal",      "2X Coin",
    "3X Crystal",      "Coin",
    "4X Crystal",      "2X Coin",
    "VP Point",        "VP Point"
};

string actions[] = {
    "2-Place new armies",             "4-Move armies",
    "2-Move over land/water",         "Build City",
    "Destroy army",                   "2-Move armies OR Destroy army", 
    "Destroy army OR Build City",     "4-Place new armies OR 3-Move over land/water",
    "3-Move armies AND Destroy army", "Build City AND 3-Move armies",
    "Destroy army AND Build City",    "4-Place new armies AND 4-Move over land/water",
    "3-Place new armies",             "4-Move armies",
    "2-Move over land/water",         "Build City",
    "Destroy army",                   "4-Move armies OR Destroy army", 
    "Destroy army OR Build City",     "3-Place new armies OR 2-Move over land/water",
    "2-Move armies AND Destroy army", "Build City AND 2-Move armies",
    "Destroy army AND Build City",    "3-Place new armies AND 3-Move over land/water",
    "2-Place new armies",             "2-Move armies",
    "2-Move over land/water",         "Build City",
    "Destroy army",                   "3-Move armies OR Destroy army", 
    "Destroy army OR Build City",     "2-Place new armies OR 3-Move over land/water",
    "2-Move armies AND Destroy army", "Build City AND 3-Move armies"
};

/*Structure Card*/
Card::Card()
{
    title = "";
    good = "";
    action = "";
}

Card::Card(string t,string g,string a)
{
    title = t;
    good = g;
    action = a;
}


Card::Card(const Card &C)
{
    title = C.title;
    good = C.good;
    action = C.action;
}

void Card::show()
{ cout<<title<<setw(30)<<good<<setw(50)<<action<<"\n"; }

string Card::toString()
{ return title+"\t\t"+good+"\t\t"+action; }


Card Card::operator = (Card* obj)
{
    title = obj->title;
    good = obj->good;
    action = obj->action;

    return *this;
}

Card::~Card() {}

ostream& operator << (ostream& out, Card& obj)
{
    out << obj.title << setw(30) << obj.good << setw(50) << obj.action << "\n";
    return out;
}

/*Class Deck*/

//Constuctor Chaining is not allowed


Deck::Deck(int number_of_players = 2)
{
    curr_top = 0;

    //Determing the number of cards from the number of players
    if ( number_of_players == 2 )
        number_of_cards = 27;
    
    else if ( number_of_players == 3 )
        number_of_cards = 32;

    else 
        number_of_cards = 34;

    //Creating pack_of_cards array which will store all the cards
    pack_of_cards = new Card[number_of_cards];

    for ( int i = 0; i < number_of_cards; ++i )
        pack_of_cards[i] = Card(titles[i],goods[i],actions[i]);

    random_shuffle(pack_of_cards, pack_of_cards + number_of_cards); 
    //Shuffles the deck randomly
}


Deck::Deck(const Deck &D)
{
    number_of_cards = D.number_of_cards;

    pack_of_cards = new Card[number_of_cards];

    for ( int i = 0; i < number_of_cards; ++i )
        pack_of_cards[i] = Card(titles[i],goods[i],actions[i]);

    random_shuffle(pack_of_cards, pack_of_cards + number_of_cards);
}

Deck Deck::operator = (Deck* obj)
{
    number_of_cards = obj->number_of_cards;

    pack_of_cards = new Card[number_of_cards];

    for (int i = 0; i < number_of_cards; ++i)
        pack_of_cards[i] = Card(titles[i], goods[i], actions[i]);

    random_shuffle(pack_of_cards, pack_of_cards + number_of_cards);

    return *this;
}

void Deck::Show()
{  
    for ( int i = 0; i < number_of_cards; ++i )
        pack_of_cards[i].show();
}


Card* Deck::draw()
{
    return &pack_of_cards[curr_top++];
}

ostream& operator << (ostream& out, Deck& obj)
{
    for (int i = 0; i < obj.number_of_cards; ++i)
        out << obj.pack_of_cards[i];

    return out;
}


Deck::~Deck()
{
    delete[] pack_of_cards;
    cout<<"Destroyed Deck Object\n";
}



/*Class Hand*/

Hand::Hand() : Hand::Hand(2) {}

Hand::Hand(int number_of_players = 2) 
{
    numOfplayers = number_of_players;
    deck = new Deck(number_of_players);

    for (int i = 0; i < 6; ++i)     //Adding 6 cards to the faceup_cards array
        faceup_cards.push_back( deck->draw() );    
}


Hand::Hand( Hand* H )  
{
    deck = new Deck(H->numOfplayers);
    
    numOfplayers = H->numOfplayers;

    for (int i = 0; i < 6; ++i)
        faceup_cards.push_back( deck->draw() );
}


Hand Hand::operator = (Hand* obj)
{
    deck = obj->deck;
    for (int i = 0; i < 6; ++i)
        faceup_cards.push_back( deck->draw() );

    return *this;
}

void Hand::Show()
{
    cout<<"FACEUP CARDS"<<"\n-------------------------------------------\n";
    cout<<"Cost: "<<0<<setw(20);
    faceup_cards.at(0)->show();

    cout<<"Cost: "<<1<<setw(20);
    faceup_cards.at(1)->show();

    cout<<"Cost: "<<1<<setw(20);
    faceup_cards.at(2)->show();

    cout<<"Cost: "<<2<<setw(20);
    faceup_cards.at(3)->show();

    cout<<"Cost: "<<2<<setw(20);
    faceup_cards.at(4)->show();

    cout<<"Cost: "<<3<<setw(20);
    faceup_cards.at(5)->show();

    cout<<"\n";
}


Card Hand::exchange(int pos)
{
    Card *temp = faceup_cards.at(pos); //Selects the card at specific index
    faceup_cards.erase(faceup_cards.begin()+pos);   //removes it from faceup_cards

    faceup_cards.push_back( deck->draw() ); //Adding a new card to the back of faceup_cards

    return *temp;
}

Hand::~Hand()
{
    faceup_cards.clear();
    cout<<"Destroyed Hand Object\n";
}


//------------------------------------Operator overloading------------------------------

ostream& operator << (ostream& out, Hand& obj)
{
    out << "FACEUP CARDS" << "\n-------------------------------------------\n";
    out << "Cost: " << 0 << setw(20);
    out << obj.faceup_cards.at(0);

    out << "Cost: " << 1 << setw(20);
    out << obj.faceup_cards.at(1);

    out << "Cost: " << 1 << setw(20);
    out << obj.faceup_cards.at(2);

    out << "Cost: " << 2 << setw(20);
    out << obj.faceup_cards.at(3);

    out << "Cost: " << 2 << setw(20);
    out << obj.faceup_cards.at(4);

    out << "Cost: " << 3 << setw(20);
    out << obj.faceup_cards.at(5);

    out << "\n";
    return out;
}
