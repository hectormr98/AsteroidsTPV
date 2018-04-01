#include "Bullet.h"
#include"BasicMotionPhysics.h"


Bullet::Bullet(SDLGame* game):Container(game)
{
	setActive(true);
	setHeight(5);
	setWidth(5);
	addPhysicsComponent(new BasicMotionPhysics());//hacerlo mas adelante en el manager
}


Bullet::~Bullet()
{
}

void Bullet::setFighterId(int id) { fighterId = id; }

int Bullet::getFighterId() { return fighterId; }
