#pragma once
#include "PhysicsComponent.h"
#include "Timer.h"

class BadgeTimer : public PhysicsComponent {
public:
	BadgeTimer();
	virtual ~BadgeTimer();
	virtual void update(GameObject* o, Uint32 time);
	void start(Uint32 timeInterval);
private:
	bool on_;
	//Uint32 timeOn_;  //timer->TimeSinceTimerCreation
	Uint32 timeInterval_;
	Timer* timer;
};

