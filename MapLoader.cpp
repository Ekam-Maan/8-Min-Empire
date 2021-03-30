#include <iostream>
#include <string>
#include <fstream>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

MapLoader::MapLoader()
{}

MapLoader::MapLoader(const MapLoader&){}

void MapLoader::operator= (const MapLoader&){}

ostream& operator<< (ostream& out, MapLoader& ml){}

MapLoader ::~MapLoader()
{
	cout << "\nMapLoader Destructor called.\n";
}


// this method will load the board and will ask user to select the required configration and will validate the loaded map.
Graph* MapLoader::loadBoard() 
{
	string rec = "B1.txt"; // rectangular config
	string lsh = "B2.txt"; // L-shaped config
	char c;
	int numV, numCont;
	int r1, r2, type, cont_id;
	ifstream loader;

	cout << "Type R for Rectangle configuration or L for L-Shape configuration: ";
	cin >> c;

	if (c == 'R')
		loader.open(rec);

	else
		loader.open(lsh);
	
	loader >> numV; // getting number of vertices from the file
	
	loader >> numCont; // getting number of Continents from the file
	
	Graph* g = new Graph(numV,numCont);

	for (int i = 0; i < numV; i++) { // getting and setting the continent ID of each Region
		loader >> cont_id;
		g->arr[i].t->setCont_id(cont_id);
	}

	while (loader >> r1 >> r2 >> type)// loading Map
	{
		addEdge(g, r1, r2, type);
		
	}

	loader.close();

	g->validate(); // vaidating Map

	return g;
}

