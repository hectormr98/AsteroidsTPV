#pragma once
#include"Container.h"

class Asteroid : public Container
{
private:
	int generation;
public:
	Asteroid(SDLGame* game);
	virtual ~Asteroid();
	virtual void setGeneration(int gen) { generation = gen; };
	virtual int getGeneration() { return generation; };
};

