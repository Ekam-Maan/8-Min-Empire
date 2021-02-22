#include <iostream>
#include <string>
#include "bidding.cpp"
#include <cstdlib>
#include "player.h"
using namespace std;
int main() {

   /* player *p1 =new player("ekam", "maan");
    cout << p1->firstName<< endl;
    cout << p1->secondName << endl;
    cout << p1->amount << endl;
    delete p1;
    p1 = NULL;*/

    
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



}
