#include <iostream>
#include <string>
#include <fstream>
#include "MapLoader.h"
#include "Map.h"

using namespace std;

MapLoader::MapLoader() 
{}

MapLoader ::~MapLoader() 
{
	cout << "\nMapLoader Destructor called.\n";
}

Graph* MapLoader::loadBoard()
{
	string rec = "B1.txt"; // rectangular config
	string lsh = "B2.txt"; // L-shaped config
	char c;
	int numV,numCont ;
	int r1, r2, type, cont_id;
	ifstream loader;

	cout << "Type R for Rectangle configuration or L for L-Shape configuration: ";
	cin >> c;

	if (c == 'R')
		loader.open(rec);

	else
		loader.open(lsh);

	loader >> numV;
	loader >> numCont;
	//cout << numV;
	Graph* g = new Graph(numV, numCont);
	for (int i = 0; i < numV; i++) {
		loader >> cont_id;
		g->arr[i].t->setCont_id(cont_id);
	}

	while (loader >> r1 >> r2 >> type)
	{
		addEdge(g, r1, r2, type);
		//cout << r1 << ", " << r2 << ", " << type<<"\n";
	}

	loader.close();
	validate(g);

	return g;
}


