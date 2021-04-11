#include "GameObservers.h"

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

void Subject::notify(string message) 
{
	list<Observer*>::iterator i;

	for ( i = _observers->begin(); i != _observers->end(); ++i )
		(*i)->update(message);
};


Subject::~Subject()
{
	//list<Observer*>::iterator i;
	//for ( i = _observers->begin(); i != _observers->end(); ++i )
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

void PhaseObserver::update(string message)
{
	cout << message;
}