#include "Cards.cpp"
#include <iostream>

using namespace::std;

int main()
{
    Hand* obj = new Hand();
    obj->Show();

    Card card = obj->exchange(2);

    obj->Show();
    
    delete obj;

    return 0;
}

//CardsDriver.exe