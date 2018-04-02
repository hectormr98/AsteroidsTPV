#pragma once
#include"GameObject.h"
#include"Bullet.h"
#include"Observable.h"
#include"Observer.h"

class BulletsManager: public Observable, public Observer
{
private:
	virtual void Shoot(GameObject* o, Vector2D p, Vector2D v);
public:
	BulletsManager();
	~BulletsManager();
	virtual std::vector<Bullet*>& getBullets() = 0;
};

