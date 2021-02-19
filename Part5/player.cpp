#include <iostream>
#include <string>
#include <cstdlib>
#include "player.h"
getAmount ();

class player
{
public:	//access control
  string firstName;
  string secondName;
  int amount;			
   
    // Constructor with parameters
    player (string fName, string lName)
  {				
    firstName = fName;
    secondName = lName;
    amount = getAmount ();
  }
// the method generates a random number aka the number they'll bid and assigns it to each player.

  int getAmount ()
  {
    int randomNumber = rand () * 9;
    return randomNumber;
  }

};
