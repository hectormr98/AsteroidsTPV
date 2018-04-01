#include "RotationPhysics.h"



RotationPhysics::RotationPhysics(double n):PhysicsComponent()
{
	int aux = rand() % 2;
	if (aux == 0)
		rotate = -n;
	else rotate = n;
}


RotationPhysics::~RotationPhysics()
{
}

void RotationPhysics::update(GameObject* o, Uint32 time) {
	Vector2D aux = o->getDirection();
	aux.rotate(rotate);
	o->setDirection(aux);
}