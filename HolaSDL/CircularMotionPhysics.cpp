#include "CircularMotionPhysics.h"



CircularMotionPhysics::CircularMotionPhysics() :PhysicsComponent()
{
}


CircularMotionPhysics::~CircularMotionPhysics()
{
}

void CircularMotionPhysics::update(GameObject* o, Uint32 time) {
	double x = o->getPosition().getX();
	double y = o->getPosition().getY();
	if (x >= o->getGame()->getWindowWidth()) {
		x = 0 - o->getWidth();
	}
	else if (x + o->getWidth() <= 0) {
		x = o->getGame()->getWindowWidth();
	}

	if (y >= o->getGame()->getWindowHeight()) {
		y = 0 - o->getHeight();
	}
	else if (y + o->getHeight() <= 0) {
		y = o->getGame()->getWindowHeight();
	}
	Vector2D aux(x, y);

	o->setPosition(aux);
}
