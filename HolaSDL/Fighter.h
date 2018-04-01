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
};

