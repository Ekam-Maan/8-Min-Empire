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
	string rec = "B1.txt";
	string lsh = "B2.txt";
	char c;
	int numV;
	int r1, r2, type;
	ifstream loader;
	
	cout << "Type R for Rectangle configuration or L for L-Shape configuration: ";
	cin >> c;
	
	if (c == 'R') 
		loader.open(rec);
	
	else 
		loader.open(lsh);
	
	loader >> numV;
	//cout << numV;
	Graph* g = new Graph(numV);

	while (loader >> r1 >> r2 >> type) 
	{
		addEdge(g, r1, r2, type);
		//cout << r1 << ", " << r2 << ", " << type<<"\n";
	}

	loader.close();
	validate(g);

	return g;
}

