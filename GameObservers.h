#pragma once
#include<iostream>
#include <list>
#include <string>

using namespace::std;

class Subject;
class Observer;

class Subject 
{
private:
	list<Observer*>* _observers;

public:
	Subject();
	virtual void attach(Observer* obj);
	virtual void detach(Observer* obj);
	virtual void notify(string message);
	~Subject();
};


class Observer
{
private:
	Subject* sub;
public:
	Observer() = default;
	Observer(Subject* s);
	virtual void update(string message) = 0;
};


class PhaseObserver : public Observer
{
public:
	PhaseObserver(Subject* sub);
	void update(string message);
};

