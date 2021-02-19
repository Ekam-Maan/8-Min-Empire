#include <iostream>
#include <string>
#include "player.cpp"
#include "bidding.cpp"
#include <cstdlib>

int main(){
    
    string Name; player PlayObj[];
    for (i=1;i=<5;i++){
    cout << "whats the name of player " << i; 
    std::string name = cin >> Name;
    std::size_t pos = name.find(" ");
    
    PlayObj[i] = new player(name.substr(0, pos), name.substr(pos, std::string::npos));
    }
    
    
    bidding bidder = new bidding( PlayObj[0], PlayObj[1], PlayObj[2], PlayObj[3], PlayObj[4] );
    string Winner = bidder.nameComparison();
    cout << "The Winner is " << Winner; 
    
    
}