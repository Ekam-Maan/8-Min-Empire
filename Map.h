#pragma once
#include<string>
#include <unordered_map>
using namespace std;


class Territory { // it represent a region/country
private:
	string name;
	unordered_map<string, int> *armylist;
	unordered_map<string, int> *citylist;
	string owner;
	int id;
	int cont_id;
public:
	int getnumOfarmies(string name);
	int getID();
	int getCID();
	string getOwner();
	int getnumOfcities(string name);
	void setCont_id(int cid);
	void updatearmylist(string name, int ChangeInnumOfarmies);
	void updatecitylist(string name, int ChangeInnumOfcities);
	void printRegionDetails();

	void updateowner();
	Territory();
	Territory(const Territory&);
	void operator = (const Territory&);
	~Territory();

	friend ostream& operator << (ostream& out, Territory& obj);
	friend istream& operator >> (istream& in, Territory& obj);
	Territory(string s, int id);
};


struct AdjlistNode { // this is a link list that each vertex has its own. it represents the information of the adjacant regions

	int id;
	bool type; //this represent type of connection between two node (0=land 1=water)
	AdjlistNode* next;

	AdjlistNode();
	AdjlistNode(int, bool, AdjlistNode*);
	AdjlistNode(const AdjlistNode& adj);
	void operator= (const AdjlistNode& adj);
	~AdjlistNode();
	friend ostream& operator<< (ostream& out, AdjlistNode& adj);
	
};

struct Vertex {// each vertex stores a pointer to a region and a header pointer to a link list(which store infomation of its adjacant regions)
	Territory* t;
	int id;
	AdjlistNode* head;

	Vertex();
	Vertex(const Vertex& v);
	void operator= (const Vertex&);
	Vertex(int id, AdjlistNode* head);
	~Vertex();
	friend ostream& operator<< (ostream& out, Vertex& adj);
};


struct Graph { // this represent the whole map 
	int V;
	int cont;
	int numOfPlayers;
	Vertex* arr; // it is the array consisting all vertices (a vertex =(Region + list of its adjacant regions))
	Graph();
	Graph(const Graph& g);
	void operator= (const Graph& g);
	friend ostream& operator << (ostream& out, Graph& g);
	Graph(int v, int cont);
	~Graph();
	void setnumOfPlayer(int np);
	int getNumOfPlayers();
	void placeNewArmies(string name, int numOfArmies, int dest);
	void moveArmies(string name, int moveArmy, int src, int dest);
	void buildCity(string name, int dest);
	void destroyArmy(string name, int numOfCount, int dest);
	void printGraph();
	void validate();

};

void addEdge(Graph* arr, int src, int dest, bool type); // src= id of first region ; dest= id of second region;
bool isAdj(Graph* g, int id1, int id2); // pass the IDs of the vertices/regions you want to check weather or not they are adjacant or not;
bool isLandConn(Graph* g, int id1, int id2);


