#include "Player.h"
#include <queue>

using namespace std;

class biddingfacility
{   
    private:
        int winningbid;
    public:
        queue<Player> bid( Player*, int );
        biddingfacility();
        biddingfacility(biddingfacility* obj);
        biddingfacility operator = (biddingfacility* obj);
        friend ostream& operator << (ostream& out, biddingfacility* obj);
};
