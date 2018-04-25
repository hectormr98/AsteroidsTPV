#pragma once
#include"Container.h"
class Fighter:public Container
{
private:
	int id_;


public:
	Fighter(SDLGame* game, int id);
	~Fighter();
	int getId();
	int badgeType = 0;
	bool badgeOn = false;
	int getBadge() { if (badgeOn) return badgeType; else return 0; }
};

