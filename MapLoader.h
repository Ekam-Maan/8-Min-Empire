#include "Map.h"

#pragma once
using namespace std;

class MapLoader 
{
	public:
		MapLoader();
		MapLoader(const MapLoader &);
		void operator= (const MapLoader&);
		friend ostream& operator<< (ostream& out, MapLoader& ml);
        static Graph* loadBoard();
		~MapLoader();

};
