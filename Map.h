#pragma once
#include<string>
#include <unordered_map>
using namespace std;


class Territory { // it represent a region/country
private:
	string name;
	unordered_map<string, int> armylist;
	unordered_map<string, int> citylist;
	string owner;
	int id;
	int cont_id;
public:
	int getnumOfarmies(string name) { return armylist[name]; }
	int getID() { return id; }
	int getCID() { return cont_id; }
	int getnumOfcities(string name) { return citylist[name]; }
	void setCont_id(int cid) {
		cont_id = cid;
	}
	void updatearmylist(string name, int ChangeInnumOfarmies);
	void updatecitylist(string name, int ChangeInnumOfcities);
	void printRegionDetails();

	void updateowner();
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
	Vertex* arr; // it is the array consisting all vertices (a vertex =(Region + list of its adjacant regions))
	Graph();
	~Graph();
	Graph(int v);
	void placeNewArmies(string name, int numOfArmies, int dest);
	void moveArmies(string name, int moveArmy, int src, int dest);
	void buildCity(string name, int dest);
	void destroyArmy(string name, int numOfCount, int dest);


};

void addEdge(Graph* arr, int src, int dest, bool type); // src= id of first region ; dest= id of second region;
void validate(Graph* g);
bool isAdj(Graph* g, int id1, int id2); // pass the IDs of the vertices/regions you want to check weather or not they are adjacant or not;
bool isLandConn(Graph* g, int id1, int id2);
void printGraph(Graph* g);
bool moveOverLand(Graph* g, string name, int move);

