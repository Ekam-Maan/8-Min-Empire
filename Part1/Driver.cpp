//#include<iostream>
#include<string>
#include"map.h"
#include<iostream>
using namespace std;


int main() {
   // -------------------------disclaimer: pls use maploader class to create map for the game-------------------------
Graph* map = new  Graph(4); 
    // adding edge between two nodes with the indication to the type of edge(0=land, 1=water)
   addEdge(map,0, 1, 0); // ( (0,1,0) first 0 represents id of first region: 1 represent id of second region and last zero represents type of edge
   addEdge(map, 0, 2, 1);
   addEdge(map, 0, 3, 0);
   addEdge(map, 3, 2, 1);
   addEdge(map, 3, 1, 0);

  

   printGraph(map);
   validate(map);
   if (isLandConn(map, 2, 0)) {
       cout << "\n yes";
   }
   else {
       cout << "\nNO, the regions are NOT adjacant.";
   }

   delete map;
   map = NULL;
   return 0;
}