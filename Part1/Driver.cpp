#include<iostream>
#include<string>
#include"Map.cpp"
using namespace std;


int main() {
   // -------------------------DISCLAIMER: PLS USE MAPLOADER CLASS TO CREATE MAP FOR THE GAME-------------------------
Graph* map = new  Graph(4); 
    // adding edge between two nodes with the indication to the type of edge(0=land, 1=water)
   addEdge(map,0, 1, 0); // ( (0,1,0) first 0 represents id of first region: 1 represent id of second region and last zero represents type of edge
   
   addEdge(map, 0, 2, 1);
   addEdge(map, 0, 3, 0);
   addEdge(map, 3, 2, 1);
   addEdge(map, 3, 1, 0);

   printGraph(map);
   validate(map);

   delete map;
   map = NULL;
   return 0;
}