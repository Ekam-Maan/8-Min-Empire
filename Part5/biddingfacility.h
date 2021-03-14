#include "../Part3/Player.cpp"
#include <queue>

using namespace std;

class biddingfacility
{   
    private:
        int winningbid;
    public:
        queue<Player> bid( Player[], int );
};
