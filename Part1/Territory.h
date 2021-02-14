#pragma once
#include<string>
using namespace std;

class Territory {
private:
	string name;
	int id;
public:
	Territory();
	Territory(string s, int id);
};