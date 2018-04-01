#include "Fighter.h"



Fighter::Fighter(SDLGame* game, int id) : Container(game)
{
	setActive(true);
	setHeight(50);
	setWidth(50);
	setVelocity(Vector2D(0, 0) ) ;
	id_ = id;
}


Fighter::~Fighter()
{
}

int Fighter::getId() { return id_; };
