#include <iostream>
#include "player.cpp"
#include "main.cpp"
#include <string>
#include <algorithm>
#include "bidding.h"
std nameComparison ();

class bidding
{
public:			// Access specifier
  player p1;
  player p2;
  player p3;
  player p4;
  player p5;
  player winningPlayer;		// Attributes

    bidding (player * p1, player * p2, player * p3, player * p4, player * p5)
  {
    p1 = *p1;
    p2 = *p2;
    p3 = *p3;
    p4 = *p4;
    p5 = *p5;
  }
  player playerObjects[] = { p1, p2, p3, p4, p5 };

  string nameComparison ()
  {

    int arr[] = { playerObjects[0]->amount, playerObjects[1]->amount,
      playerObjects[2]->amount, playerObjects[3]->amount,
      playerObjects[4]->amount
    };
    //sort method will arrange the array of bidding numbers in descending to ascending order.
    //the bidding number indexed 0 has the highest bidding number

    // now compare all the elements with arr[0] that has the highest bidding number 
    //if bidding number is same or zero the compare method will compare the lastName.
    int max = 0;
    int counter = 0;
    string winner;

    for (int i = 0; i < playerObjects.size (); i++)
      {
	winningPlayer = playerObjects[i];
	for (int j = i; j < player.size (); j++)
	  {
	    player runnerUp = playerObjects[j];
	    if (playerObjects[i]->amount <= playerObjects[j]->amount)
	      {
		if (max < playerObjects[j]->amount)
		  max = runnerUp->amount;
	      }
	  }
      }
    for (int i = 0; i < playerObjects.size (); i++)
      {				//for every single i compare it with j with same amount; the counter tell us
	for (int j = 0; j < playerObjects.size (); j++)
	  {			// considering that the amount is maximum and amount bid are same i.e tied,we compare their lastnames to realise

	    if (playerObjects[i]->amount == max
		&& playerObjects[i]->amount == playerObjects[j]->amount)
	      {
		if ((playerObjects[i]->lastname.
		     compare (playerObjects[j]->lastname) < 0) winner =
		    playerObjects[i]->lastname;
		    else
		    winner = playerObjects[j]->lastname;
		    if ((playerObjects[0]->lastname.
			 compare (playerObjects[j]->lastname)) == 0) winner =
		    playerObjects[i]->lastname;}
		    }
		    }
		    }



		    };
