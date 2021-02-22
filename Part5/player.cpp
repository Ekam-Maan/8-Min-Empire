#include<cstdlib>
#include"player.h"
using namespace std;

//from anywhere
player::player() {
	cout << "Default constructer of PLAYER called.";
}
player::player(string fName, string lName, int amt)
{				// Constructor with parameters
	firstName = fName;
	secondName = lName;
	amount = amt;
}
player::player(string fName, string lName)
{				// Constructor with parameters
	firstName = fName;
	secondName = lName;
	amount = getAmount();
}
player::~player() {
	cout << "\nplayer destructer called";
}
// the method generates a random number aka the number they'll bid and assigns it to each player.

int player::getAmount()
{
    srand(time(0));
	int randomNumber = (rand()  % 100)+1;
	return randomNumber;
  
 
}