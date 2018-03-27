#include "BulletsManager.h"



BulletsManager::BulletsManager()
{
}


BulletsManager::~BulletsManager()
{
}

void BulletsManager::Shoot(GameObject* o, Vector2D p, Vector2D v) {
	o->setPosition(p);
	o->setVelocity(v);
}
