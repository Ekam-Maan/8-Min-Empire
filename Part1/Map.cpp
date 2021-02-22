#include<string>
#include<iostream>
#include"Map.h"

static int sid = 0;

AdjlistNode::AdjlistNode():id( -1),type(0),next(NULL) {
}
AdjlistNode::~AdjlistNode() {
	delete next;
	next = NULL;
	//cout << "\n AdjlistNode object DESTROYED.";
}


AdjlistNode::AdjlistNode(int id, bool tp, AdjlistNode* nxt) : id(id), type(tp), next(nxt){
}

Vertex::Vertex() : t(nullptr), id(sid++), head(nullptr) {
}
Vertex::~Vertex() {
	//t->~Territory();
	delete t;
	t = NULL;
	delete head;
	head = NULL;
	//cout << "\nVertex object DESTROYED.";
}
Vertex::Vertex( int id, AdjlistNode* hd) :id(sid++), head(nullptr) {
	string name = "T" + id;
	t = new Territory(name, id);
}

Territory::Territory() : name("not defined"), id(-1) {}
Territory::Territory(string s, int id1) : name(s), id(id1) {}
Territory::~Territory() {
	cout << "\nTerritory object DESTROYED.";
}
Graph::Graph():V(0){
	arr = new Vertex[0];
}

Graph::~Graph() {
	delete[] arr;
	cout << "\nAll Vertex objects are DESTROYED. ";
	arr = NULL;
	cout << "\nGraph object DESTROYED.";
}

Graph::Graph(int v):V(v){
	arr = new Vertex[v];
}

bool isAdj(Graph* g, int id1, int id2) { // pass the IDs of the vertices/regions you want to check weather or not they are adjacant or not
	AdjlistNode* itr;
	itr= g->arr[id1].head;
	while (itr != NULL) {
		if (itr->id == id2) {
			return true;
		}
		itr = itr->next;
	}
	return false;
}
bool isLandConn(Graph* g, int id1, int id2) {
	AdjlistNode* itr;
	itr = g->arr[id1].head;
	while (itr != NULL) {
		if (itr->id==id2 && itr->type) {
			return true;
		}
		itr = itr->next;
	}
	return false;
}

void addEdge(Graph* g, int src, int dest, bool type) {
	AdjlistNode* ptr = new AdjlistNode(dest, type, NULL); // creating node 
	ptr->next = g->arr[src].head;
	g->arr[src].head = ptr;

	ptr = new AdjlistNode(src, type, NULL);
	ptr->next = g->arr[dest].head;
	g->arr[dest].head = ptr;
};

void printGraph(Graph* g) {
	for (int i = 0; i < g->V; i++) {
		AdjlistNode* itr = g->arr[i].head;
		cout << "\nAdjacency list of vertex " << i << endl;
		while (itr != NULL) {
			if (itr->type == 0) {
				cout << " ->[" << itr->id << "-Land]";
			}
			else {
				cout << " ->[" << itr->id << "-Water]";
			}
			itr = itr->next;
		}
		cout << endl;

	}
}

void validate(Graph* g) {
	int nedge = 0;
	for (int i = 0; i < g->V; i++) {
		AdjlistNode* itr=g->arr[i].head;
		
		while (itr != NULL) {
			nedge++;
			itr = itr->next;
		}
	}
	if (((nedge / 2) - (g->V)) >= -1) {
		cout << "\nThe graph is VALID [:-)}  ";
	}
	else {
		cout << "\nThe graph is INLVALID [:-(} ";
	}
}



