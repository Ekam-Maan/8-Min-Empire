#pragma once
#include<string>
#include"Territory.h"
using namespace std;




class Territory { // it represent a region/country
private:
	string name;
	//int numofArmies;
	int id;
public:
	Territory();
	~Territory();
	Territory(string s, int id);
};


struct AdjlistNode { // this is a link list that each vertex has its own. it represents the information of the adjacant regions

	int id;
	bool type; //this represent type of connection between two node (0=land 1=water)
	AdjlistNode* next;

	AdjlistNode();
	~AdjlistNode();
	AdjlistNode(int, bool, AdjlistNode*);
};

struct Vertex {// each vertex stores a pointer to a region and a header pointer to a link list(which store infomation of its adjacant regions)
	Territory* t;
	int id;
	AdjlistNode* head;

	Vertex();
	~Vertex();
	Vertex(int id, AdjlistNode* head);
};


struct Graph { // this represent the whole map 
    int V;
    Vertex* arr; // it is the array consisting all vertices( a vertex =(Region + list of its adjacant regions))

	Graph();
	~Graph();
	Graph(int v);
	
};

void addEdge(Graph* arr, int src, int dest, bool type); // src= id of first region ; dest= id of second region;
void validate(Graph* g);
void printGraph(Graph* g);

