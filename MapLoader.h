#include "Map.h"

#pragma once
using namespace std;

class MapLoader 
{
	public:
		MapLoader();
		static Graph* loadBoard();
		~MapLoader();

};
