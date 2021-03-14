#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include "../Part1/Map.h"
using namespace std;
class MapLoader {
public:
	Graph* g= nullptr;
	MapLoader();
	~MapLoader();
	void loadBoard();

};
