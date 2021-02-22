#include <iostream>
#include "player.h"
#include <string>
#include <algorithm>
using namespace std;
class bidding
{
	// Access specifier
public:
	player *winningPlayer;	// Attribute
	player** playerObj= new player *[5];
	bidding()
	{}

	bidding(player* p1, player* p2, player* p3, player* p4, player* p5)
	{
		playerObj[0] = p1;
		playerObj[1] = p2;
		playerObj[2] = p3;
		playerObj[3] = p4;
		playerObj[4] = p5;
	}

	
	string nameComparison()
	{
// create an  array and add all the amounts bidded by the players
		int arr[] = { playerObj[0]->amount, playerObj[1]->amount,
		  playerObj[2]->amount, playerObj[3]->amount,
		  playerObj[4]->amount
		};
		cout << "\n" <<endl;
		// prints the amount bid by all players
		for (int i = 0; i < 5; i++) {
			cout << playerObj[i]->firstName << " " << playerObj[i]->secondName << " bidded " << playerObj[i]->amount << " coins."<<endl;
		}
		//sort method will arrange the array of bidding numbers in descending to ascending order.
		//the bidding number indexed 0 has the highest bidding number

		// now compare all the elements with arr[0] that has the highest bidding number 
		//if bidding number is same or zero the compare method will compare the lastName.
		int max = 0;
		int counter = 0;
		string winner;int winnerid=0; 

		for (int i = 0; i < 5; i++)
		{
			winningPlayer = playerObj[i];
			for (int j = i; j < 5; j++)
			{
				player* runnerUp = playerObj[j];
				if (playerObj[i]->amount <= playerObj[j]->amount)
				{
					if (max < playerObj[j]->amount)
						{max = runnerUp->amount; winnerid = j;}
				}
			}
		}
		
		int globalmin =0;
		for (int i = 0; i < 5; i++)
		{//for every single i compare it with j with same amount; the counter tell us
			for (int j = i; j < 5; j++)
			{

				if (playerObj[i]->amount == max && playerObj[i]->amount == playerObj[j]->amount)
				{
				    int local = (playerObj[i]->secondName.
                        compare(playerObj[j]->secondName));
                    if (local<globalmin)
                    {    
                        cout << " bidded " << playerObj[j]->secondName <<endl;
                        globalmin = local;
                        winnerid = i;
                        //winner = playerObj[i]->secondName;
                    }
				// 	if ((playerObj[i]->secondName.compare(playerObj[j]->secondName) < 0))
				// 	{
				// 	    //winner = playerObj[i]->secondName;
				// 		winnerid = i;
						
						
				// 	}
				// 	else{
				// 		//winner = playerObj[j]->secondName;

				// 		winnerid = j;
				// 	}
				// 	if ((playerObj[i]->secondName.compare(playerObj[j]->secondName)) == 0) {
				// 		//winner =playerObj[i]->secondName;
				// 		winnerid = i;
				// 	}
				}
			}
		}
		winner = playerObj[winnerid]->firstName +" "+ playerObj[winnerid]->secondName;
		delete[] playerObj;
		playerObj = NULL;
		return (winner);
	}
	

};

//player playerObjects[] = { p1, p2, p3, p4, p5 };



		  
