#include <string>
#pragma once

using namespace::std;


struct Card
{
    string title,good,action;
    Card();
    Card(string t,string g,string a);
    string show();
};


class Deck
{
    private:
        int number_of_cards;
        Card* pack_of_cards;
        int curr_top;
    public:
        Deck(int number_of_players);
        void Show();
        Card draw();
        ~Deck();
};

class Hand
{
    
};

