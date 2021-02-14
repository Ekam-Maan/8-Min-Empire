#include<string>
#include<iostream>;
#include"Map.h"

AdjlistNode::AdjlistNode():id(-1),type(0),next(NULL) {
}
AdjlistNode::~AdjlistNode() {
	delete next;
	next = NULL;
}


AdjlistNode::AdjlistNode(int id1, bool tp, AdjlistNode* nxt) : id(id1), type(tp), next(nxt){
}

Vertex::Vertex() : t(nullptr), id(-1), head(nullptr) {
}
Vertex::~Vertex() {
	delete t;
	delete head;
	t = NULL;
	head = NULL;
}
Vertex::Vertex( int id, AdjlistNode* hd) :id(id), head(nullptr) {
	string name = "T" + id;
	t = new Territory(name, id);
}

Territory::Territory() : name("not defined"), id(-1) {}
Territory::Territory(string s, int id1) : name(s), id(id1) {}
Territory::~Territory() {
	cout << "Destroying Terrotory......";
}
Graph::Graph():V(0){
	arr = new Vertex[0];
}

Graph::~Graph() {
	delete[] arr;
	arr = NULL;
}

Graph::Graph(int v):V(v){
	arr = new Vertex[v];
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
		while(itr != NULL) {
			cout << " -> " << itr->id<<"tp("<<itr->type<<")";
			itr = itr->next;
		}
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



