#include<iostream>
#include<string>
#include"Map.h"
#include"Territory.h"
using namespace std;


int main() {
    int totalVertices = 4;
    Graph* graph;
    graph = new  Graph(totalVertices);
    //connect edges
    //addEdge(graph, 0, 1,0);
    //addEdge(graph, 0, 2,0);
    addEdge(graph, 0, 3,1);
    //addEdge(graph, 1, 3,1);
    addEdge(graph, 1, 2,0);

    printGraph(graph);

    validate(graph);

    delete graph;
    graph = NULL;

	return 0;
}