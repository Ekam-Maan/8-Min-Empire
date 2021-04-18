#pragma once
#include <string>
#include <vector>

#pragma once

using namespace::std;

struct Card
{
    string title,good,action;
    Card();
    Card(string t,string g,string a); 
    Card(const Card &C);
    ~Card();
    Card operator = (Card* obj);
    void show();
    string toString();
};

ostream& operator << (ostream& out, Card& obj);

//It holds all cards
class Deck
{
    private:
        int number_of_cards;
        Card* pack_of_cards;    //Pointer to a array object of type cards

        int curr_top;   //index of the current top card
                        //since we need to select a card from the top of the deck
    public:
        Deck(int number_of_players);
        Deck(const Deck &D);
        void Show();
        Card* draw();    //returns the card at index curr_top
                           //and increments 
        Deck operator = (Deck* obj);
        friend ostream& operator << (ostream& out, Deck& obj);
        ~Deck();
};

//Represents the 6 cards that are placed infront of the players from the deck
class Hand 
{
    private:
        Deck* deck;
        int numOfplayers;
        vector<Card*> faceup_cards; //Represents the 6 cards placed in front of players
        const int CardCost[6] = {0,1,1,2,2,3};
    public:
        Hand();
        Hand(int number_of_players);
        Hand(Hand* H);
        vector<Card*> getFaceUpCards();
        void Show();
        int getCardCost(int index) { return CardCost[index]; };
        Card exchange(int pos);     //Returns the card from the specified index
                                    //Moves all other cards to the left 
                                    //and adds a new card at the end;

                // faceup_cards:    Card1  Card2  Card3  Card4  Card5  Card6 
                // we call the method with index 4, the result would be
                // faceup_cards:    Card1  Card2  Card3  Card4  Card6  Card19 
                // since the next card would be picked from a shuffled deck    
        Hand operator = (Hand* obj);
        friend ostream& operator << (ostream& out, Hand& obj);
        ~Hand();
};



