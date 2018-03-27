#pragma once
#include"GameObject.h"
class BulletsManager
{
public:
	virtual void Shoot(GameObject* o, Vector2D p, Vector2D v);	
	BulletsManager();
	~BulletsManager();
};

