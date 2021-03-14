
#include<iostream>
#include <string>
#include "MapLoader.h"
#include "../Part1/Map.cpp"

using namespace std;
MapLoader::MapLoader() {
	Graph* g=NULL;
}
MapLoader ::~MapLoader() {
	cout << "\nMapLoader Destructor called.\n";
}
void MapLoader::loadBoard() {
	string rec = "B1.txt";
	string lsh = "B2.txt";
	char c;
	int numV;
	int r1, r2, type;
	ifstream loader;
	cout << "Type R for Rectangle configuration or L for L-Shape configuration: ";
	cin >> c;
	if (c == 'R') {
		loader.open(rec);
	}
	else {
		loader.open(lsh);
	}
	loader >> numV;
	g = new Graph(numV);
	while (loader >> r1 >> r2 >> type) {
		addEdge(g, r1, r2, type);
		cout << r1 << ", " << r2 << ", " << type<<"\n";
	}
	loader.close();
	printGraph(g);
	validate(g);
	delete g;
	g = NULL;
}

int main() {
	MapLoader mpl;
	mpl.loadBoard();
	return 0;
}