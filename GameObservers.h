#pragma once
#include <iostream>
#include <list>
#include <string>


using namespace::std;

class Observer;

class Subject 
{
private:
	list<Observer*>* _observers;

public:
	Subject();
	virtual void attach(Observer* obj);
	virtual void detach(Observer* obj);
	virtual void notify(string phase);
	~Subject();
};


class Observer
{
protected:
	Subject* sub;
public:
	Observer() = default;
	Observer(Subject* s);
	virtual void update(string phase) = 0;
};


class PhaseObserver : public Observer
{
private:
	PhaseObserver() = default;
public:
	PhaseObserver(Subject* sub);
	void update(string phase);
};

