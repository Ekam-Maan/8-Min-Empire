#include "Cards.h"
#include <iostream>
#include <string>
#include <queue>
#include <bits/stdc++.h>
#include <iomanip>   

using namespace::std;


/*Card Information*/
//https://cdn.1j1ju.com/medias/18/ae/df-eight-minute-empire-rulebook.pdf

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
    "3X Crystal",      "Wing",
    "4X Crystal",      "2X Wing",
    "Place Army",      "Move Army",
    "VP Point",        "Cystal AND 2X Coin",
    "Crystal",         "Coin",
    "2X Crystal",      "2X Coin",
    "3X Crystal",      "Wing",
    "4X Crystal",      "2X Wing",
    "Place Army",      "Move Army",
    "VP Point",        "Cystal AND 2X Coin",
    "Crystal",         "Coin",
    "2X Crystal",      "2X Coin",
    "3X Crystal",      "Wing",
    "4X Crystal",      "2X Wing",
    "Place Army",      "Move Army"
};

string actions[] = {
    "Place new armies",             "Move armies",
    "Move over land/water",         "Build City",
    "Destroy army",                 "Move armies OR Destroy army", 
    "Destroy army OR Build City",   "Place new armies OR Move over Land",
    "Move armies AND Destroy army", "Build City AND Move armies",
    "Destroy army AND Build City",  "Place new armies AND Move over Land",
    "Place new armies",             "Move armies",
    "Move over land/water",         "Build City",
    "Destroy army",                 "Move armies OR Destroy army", 
    "Destroy army OR Build City",   "Place new armies OR Move over Land",
    "Move armies AND Destroy army", "Build City AND Move armies",
    "Destroy army AND Build City",  "Place new armies AND Move over Land",
    "Place new armies",             "Move armies",
    "Move over land/water",         "Build City",
    "Destroy army",                 "Move armies OR Destroy army", 
    "Destroy army OR Build City",   "Place new armies OR Move over Land",
    "Move armies AND Destroy army", "Build City AND Move armies"
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

void Deck::Show()
{  
    for ( int i = 0; i < number_of_cards; ++i )
        pack_of_cards[i].show();
}


Card Deck::draw()
{
    return pack_of_cards[curr_top++];
}


Deck::~Deck()
{
    delete[] pack_of_cards;
    cout<<"Destroyed Deck Object\n";
}



/*Class Hand*/

Hand::Hand(int number_of_players = 2) : Deck(number_of_players)
{
    for (int i = 0; i < 6; ++i)     //Adding 6 cards to the faceup_cards array
        faceup_cards.push_back(draw());    
}


Hand::Hand(const Hand &H) : Deck(H)
{
    for (int i = 0; i < 6; ++i)
        faceup_cards.push_back(draw());
}


void Hand::Show()
{
    cout<<"FACEUP CARDS"<<"\n-------------------------------------------\n";
    cout<<"Cost: "<<0<<setw(20);
    faceup_cards.at(0).show();

    cout<<"Cost: "<<1<<setw(20);
    faceup_cards.at(1).show();

    cout<<"Cost: "<<1<<setw(20);
    faceup_cards.at(2).show();

    cout<<"Cost: "<<2<<setw(20);
    faceup_cards.at(3).show();

    cout<<"Cost: "<<2<<setw(20);
    faceup_cards.at(4).show();

    cout<<"Cost: "<<3<<setw(20);
    faceup_cards.at(5).show();

    cout<<"\n";
}


Card Hand::exchange(int pos)
{
    Card temp = faceup_cards.at(pos); //Selects the card at specific index
    faceup_cards.erase(faceup_cards.begin()+pos);   //removes it from faceup_cards

    faceup_cards.push_back(draw()); //Adding a new card to the back of faceup_cards

    return temp;
}

Hand::~Hand()
{
    cout<<"Destroyed Hand Object\n";
}
