#pragma once
#include"Container.h"

class Bullet:public Container
{
private:
	int fighterId;
public:
	Bullet(SDLGame* game);
	~Bullet();
	void setFighterId(int id);
	int getFighterId();
};

