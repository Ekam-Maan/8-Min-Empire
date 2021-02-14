#pragma once
#include<string>
#include"Territory.h"
using namespace std;


struct AdjlistNode { // yellow 
	int id;
	bool type; // 0=land 1=water
	AdjlistNode* next;
	AdjlistNode();
	AdjlistNode(int, bool, AdjlistNode*);
};



struct Vertex { 
	Territory* t;
	int id;
	AdjlistNode* head;
	Vertex();
	Vertex(int id, AdjlistNode* head);
};

struct Graph {
    int V;
	Vertex* arr;

	Graph();
	Graph(int v);
	
};

void addEdge(Graph* arr, int src, int dest, bool type);
void validate(Graph* g);
void printGraph(Graph* g);

