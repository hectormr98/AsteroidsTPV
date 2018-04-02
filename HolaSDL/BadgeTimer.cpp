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
		cout << timer->TimeSinceTimerCreation << endl;
		if (timer->TimeSinceTimerCreation > timeInterval_)
		{
			static_cast<GameManager*>(o)->setBadge(false);
		}
	}
}
