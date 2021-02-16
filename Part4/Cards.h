#include <string>
#include <bits/stdc++.h> 

#pragma once

using namespace::std;


struct Card
{
    string title,good,action;
    Card();
    Card(string t,string g,string a);
    Card(const Card &C);
    void show();
};


class Deck
{
    private:
        int number_of_cards;
        Card* pack_of_cards;
        int curr_top;
    public:
        Deck(int number_of_players);
        Deck(const Deck &D);
        void Show();
        Card draw();
        ~Deck();
};

class Hand : public Deck
{
    private:
        vector<Card> faceup_cards;
    public:
        Hand(int number_of_players);
        Hand(const Hand &H);
        void Show();
        Card exchange(int pos);
        ~Hand();

};

