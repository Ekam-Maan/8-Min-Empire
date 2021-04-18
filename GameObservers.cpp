#pragma once
#include "GameObservers.h"
#include "Player.h"

using namespace::std;

Subject::Subject()
{
	_observers = new list<Observer*>;
}

void Subject::attach(Observer* obj)
{
	_observers->push_back(obj);
}

void Subject::detach(Observer* obj)
{
	_observers->remove(obj);
}

void Subject::notify(string phase)
{
	list<Observer*>::iterator i;

	for ( i = _observers->begin(); i != _observers->end(); ++i )
		(*i)->update(phase);
};


Subject::~Subject()
{
	delete _observers;
	_observers = NULL;
}



//-------------------------------Observer----------------------------

Observer::Observer(Subject* s)
{
	sub = s;
	sub->attach(this);
}


//--------------------------------Phase-Observer---------------------

PhaseObserver::PhaseObserver(Subject* sub) : Observer(sub)
{}

void PhaseObserver::update(string phase)
{	
	if (Player* obj = dynamic_cast<Player*>(sub))
	{
		if ( phase == "turn" )
			cout << "\n\n" + obj->getname() + "'s turn\n\n";

		else if ( phase == "cardpicked" )
		{
			cout << "\n\n" + obj->getname() + " picked card " + to_string(obj->handList->back().second) + " from top"<<endl;
			cout << "Title: " + obj->getlastCard().title << endl;
			cout << "Good: " + obj->getlastCard().good << endl;
			cout << "Action: " + obj->getlastCard().action << endl;
		}

		else if ( phase == "Not enough money" )
			cout << "\nYou donot have enough money, pick another card";

	}

}