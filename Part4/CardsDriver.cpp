#include "Cards.cpp"

int main()
{
    
    Hand* obj = new Hand();
    obj->Show();

    obj->exchange(2);
    obj->Show();

    delete obj;

    return 0;
}

//CardsDriver.exe