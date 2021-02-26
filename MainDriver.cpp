#include<string>
#include"Part1/Map.h"
#include "Part4/Cards.cpp"
#include<iostream>
#include "Part5/bidding.cpp"
#include <cstdlib>
#include "Part5/player.h"

using namespace std;


int main() {

     //Part1
    /*
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
   */


     //Part2
    /*
    
    
    
    
    
    */



    //Part3
    /*
    
    
    */




     //Part4
    /*
        Hand* obj = new Hand();
        obj->Show();

        Card card = obj->exchange(2);

        obj->Show();
        
        delete obj;

        return 0;
    */

        //Part5
    /*
     
        player** PlayObj  = new player*[6];
        
        for (int i = 0; i <= 4 ; i++) {
            cout << "whats the name of player : " << i+1;
            std::string fname , sname;
            cin >> fname;
            cin >> sname;
            PlayObj[i] = new player(fname, sname);
            //PlayObj[i] = new player(fname, sname,0);
        // std::size_t pos = name.find(" ");
        //  PlayObj[i] = new player(name.substr(0, pos), name.substr(pos, std::string::npos));
        }

        

        bidding *bidder = new bidding(PlayObj[0], PlayObj[1], PlayObj[2], PlayObj[3], PlayObj[4]);
        string Winner = bidder->nameComparison();
        cout << "****************************************************\n";
        cout <<  Winner<<" will start the game\n";
        cout << "****************************************************\n";
        delete[] PlayObj;
        PlayObj = NULL;    
    */
}
