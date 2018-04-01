#include "AsteroidManager.h"



AsteroidManager::AsteroidManager(SDLGame* game): GameObject(game)
{
}


AsteroidManager::~AsteroidManager()
{
}

void AsteroidManager::receive(Message* msg) {
	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		break;
	case ROUND_START:
		break;
	default:
		break;
	}
}

Asteroid* AsteroidManager::getAsteroid() {
	int i = 0;
	while (i < astroids_.size() && !astroids_[i]->isActive())
		i++;
	if (i < astroids_.size())
		return astroids_[i];
	else {
		Asteroid* st = new Asteroid(game_);
		/*rotationPhysics_
		circularPhysics_ = new circularPhysics_();
		astroidImage_  = ImageRenderer(Resources::Astroid);*/
	}
}
