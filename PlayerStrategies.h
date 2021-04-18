#pragma once


class Player;

class Strategy {
public: 
	virtual void execute(Player*, Player*) = 0;
};

class HumanStrategy : public Strategy {
public:
	void execute(Player*, Player*);
};

class GreedyStrategy : public Strategy {
public:
	void execute(Player*, Player*);
};

class ModerateStrategy : public Strategy {
public:
	void execute(Player*, Player*);
	bool tryMoveOverLand(int, Player*);
	bool tryPlaceNewArmies(int, Player*);
	bool tryMoveOverWater(int, Player*);
};