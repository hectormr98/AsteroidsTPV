#pragma once
#include"Observer.h"
#include"Messages.h"

class Observable
{
private:
	std::vector<Observer*>observers_;
public:
	Observable();
	~Observable();
	virtual void registerObserver(Observer* o);
	virtual void removeObserver(Observer* o);
	virtual void send(Message* msg);
};

