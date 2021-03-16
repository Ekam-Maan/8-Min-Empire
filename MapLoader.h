#include "Map.h"

#pragma once
using namespace std;

class MapLoader 
{
	public:
		MapLoader();
		~MapLoader();
		static Graph* loadBoard();

};
