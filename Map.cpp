#include<string>
#include<iostream>
#include"Map.h"

static int sid = 0;

AdjlistNode::AdjlistNode() :id(-1), type(0), next(NULL) {
}

AdjlistNode::AdjlistNode(const AdjlistNode& adj) {
	id = adj.id;
	type = adj.type;
	next = adj.next;
};

void AdjlistNode::operator= (const AdjlistNode& adj) {
	id = adj.id;
	type = adj.type;
	next = adj.next;
};

AdjlistNode::~AdjlistNode() {
	delete next;
	next = NULL;
}


AdjlistNode::AdjlistNode(int id, bool tp, AdjlistNode* nxt) : id(id), type(tp), next(nxt) {
}

Vertex::Vertex() : id(sid++), head(nullptr) {
	string name = "T" + id;
	t = new Territory(name, id);
}
Vertex::~Vertex() {
	
	delete t;
	t = NULL;
	delete head;
	head = NULL;
	
}
Vertex::Vertex(int id, AdjlistNode* hd) :id(sid++), head(nullptr) {
	string name = "T" + id;
	t = new Territory(name, id);
}


//----------------------------Terrritory----------------------------------
Territory::Territory() : name("not defined"), id(-1)
{
	owner = "";
}

Territory::Territory(string s, int id1) : name(s), id(id1)
{
	owner = "";
}

Territory::~Territory() {
	cout << "\nTerritory object DESTROYED.";
}

Territory::Territory(const Territory& t) {
	name = t.name;
	id = sid++;
	owner = t.owner;
	cont_id = t.cont_id;
	armylist = t.armylist;
	citylist = t.citylist;
}

//-------------------------getters and setters----------------------------
int Territory::getnumOfcities(string name) { return citylist[name]; }
void Territory::setCont_id(int cid) { cont_id = cid; }
int Territory::getID() { return id; }
int Territory::getCID() { return cont_id; }
string Territory::getOwner() { return owner; }

void Territory:: operator= (const Territory & t){
	name = t.name;
	id = sid++;
	owner = t.owner;
	cont_id = t.cont_id;
	armylist = t.armylist;
	citylist = t.citylist;
}

ostream& operator << (ostream& out, Territory& t) 
{
	unordered_map<string, int>::iterator index = t.armylist.begin();
	int sn = 0;
	for (index = (t.armylist).begin(); index != (t.armylist).end(); ++index) {
		out << ++sn << ". Player Name: " << index->first << " Armies:  " << index->second << " Cities: " << t.citylist[index->first] << ".\n";
	}
	return out;
}

istream& operator >> (istream& in, Territory& t) 
{
	in >> t.name;
	in >> t.id;
	in >> t.cont_id;
	in >> t.owner;
	return in;
	
}

void Territory::updatearmylist(string name, int changeInNumOfarmy) 
{
	armylist[name] = armylist[name] + changeInNumOfarmy;
	updateowner();
}


void Territory::updatecitylist(string name, int changeInNumOfcity)
{
	citylist[name] = citylist[name] + changeInNumOfcity;
	updateowner();
}


void Territory::printRegionDetails() 
{
	unordered_map<string, int>::iterator index = armylist.begin();
	int sn = 0;
	for (index = (armylist).begin(); index != (armylist).end(); ++index) {
		cout << sn++ << ". Player Name: " << index->first << " Armies:  " << index->second << " Cities: "<<citylist[index->first] <<".\n";
	}
	
}

//Count VP for each player, Player with highest VP is owner
//if 2 players has same VP then no owner.
//army and cities are equivalent while counting VP

//Since a player can't have city where he doesn't have a army
//Iterate over amrylist and see if the player has a city.

void Territory::updateowner()
{
	int maxVP = 0;
	int temp = 0;

	unordered_map<string, int>::iterator it = armylist.begin();

	while (it != armylist.end())
	{
		temp = it->second + citylist[it->first];

		if (temp > maxVP) {
			maxVP = temp; // correctted 
			owner = it->first;
		}
			

		else if (temp == maxVP)
			owner = "";

		//temp = 0;
		++it;
	}
	
}
//------------------------------Graph---------------------------------------

Graph::Graph() :V(0) {
	arr = new Vertex[0];
}

Graph::~Graph() {

	delete[] arr;
	cout << "\nAll Vertex objects are DESTROYED. ";
	arr = NULL;
	cout << "\nGraph object DESTROYED.";
}

Graph::Graph(int v, int cont) :V(v), cont(cont) {

	arr = new Vertex[v];
}

void Graph::setnumOfPlayer(int np) { numOfPlayers = np; }
int Graph::getNumOfPlayers() { return numOfPlayers; }

void Graph::moveArmies(string name, int movearmy, int src, int dest) {

	arr[dest].t->updatearmylist(name, movearmy);
	arr[src].t->updatearmylist(name, -movearmy);

}


void Graph::placeNewArmies(string name, int numOfArmies, int dest) {

	if (dest < 0 || dest >= V) 
	{
		cout << "Destination was not found";
	}
	
	else 
	{
		(arr+dest)->t->updatearmylist(name, numOfArmies);
	}
}

void Graph::buildCity(string name, int dest) {
	arr[dest].t->updatecitylist(name, 1);
}

void Graph::destroyArmy(string name, int numOfArmies, int dest) {
	arr[dest].t->updatearmylist(name, -numOfArmies);
}

bool isAdj(Graph* g, int id1, int id2) { // pass the IDs of the vertices/regions you want to check weather or not they are adjacant or not
	AdjlistNode* itr;
	itr = g->arr[id1].head;
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
		if (itr->id == id2 && itr->type) {
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

void Graph::printGraph() 
{
	for (int i = 0; i < V; i++) 
	{
		cout << "\nShowing details of Region" << i << ": \n";
		cout<<"ID: "<< arr[i].t->getID();
		cout << "\ncont_ID: " << arr[i].t->getCID();
		arr[i].t->printRegionDetails();
		cout << "\n=============================================\n";
	}
};



void Graph::validate() {
	int nedge = 0;
	for (int i = 0; i < V; i++) {
		AdjlistNode* itr = arr[i].head;

		while (itr != NULL) {
			nedge++;
			itr = itr->next;
		}
	}
	if (((nedge / 2) - (V)) >= -1) {
		cout << "\nThe graph is VALID [:-)}  ";
	}
	else {
		cout << "\nThe graph is INLVALID [:-(} ";
	}
}



