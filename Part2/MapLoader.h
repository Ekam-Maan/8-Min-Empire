#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include"Map.h";
using namespace std;
class MapLoader {
public:
	Graph* g= nullptr;
	MapLoader();
	~MapLoader();
	void loadBoard();

};
