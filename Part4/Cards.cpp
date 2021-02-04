#include "Cards.h"
#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace::std;


/*Card Information*/

string title[] = {
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

string Card::show()
{ return title+" "+good+" "+action; }


/*Class Deck*/

//Constuctor Chaining is not allowed


Deck::Deck(int number_of_players = 2)
{
    curr_top = 0;

    if ( number_of_players == 2 )
        number_of_cards = 27;
    
    else if ( number_of_players == 3 )
        number_of_cards = 32;

    else 
        number_of_cards = 34;

    pack_of_cards = new Card[number_of_cards];

    for ( int i = 0; i < number_of_cards; ++i )
        pack_of_cards[i] = Card(title[i],title[i],title[i]);

  /*
    For randomly shuffling the array

    random_shuffle(pack_of_cards, pack_of_cards + number_of_cards);
  */  

}

void Deck::Show()
{  
    for ( int i = 0; i < number_of_cards; ++i )
        cout<<pack_of_cards[i].show()<<"\n";
}


Card Deck::draw()
{
    return pack_of_cards[curr_top++];
}


Deck::~Deck()
{
    delete pack_of_cards;
    cout<<"Destroyed Deck Object";
}



/*Class Hand*/
