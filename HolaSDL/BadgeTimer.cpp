#include "BadgeTimer.h"
#include"GameManager.h"


BadgeTimer::BadgeTimer()
{
	timer = new Timer();
}


BadgeTimer::~BadgeTimer()
{
}


void BadgeTimer::start(Uint32 timeInterval)
{
	timeInterval_ = timeInterval;
	timer->restart();
	on_ = true;
}
void BadgeTimer::update(GameObject* o, Uint32 time)
{
	if (on_)
	{
		timer->update();
		if (timer->TimeSinceTimerCreation > timeInterval_)
		{
			on_ = false;
			static_cast<GameManager*>(o)->setBadge(false);
		}
	}
}
