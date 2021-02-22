#pragma once
#include<string>
#include<iostream>
using namespace std;
struct player {
		//access control
	string firstName;
	string secondName;
	int amount;			//from anywhere
	player();
	player(string fName, string lName, int amt);
	player(string fName, string lName);
	~player();
	int getAmount();
};
