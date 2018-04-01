#pragma once
#include"PhysicsComponent.h"
class RotationPhysics:public PhysicsComponent
{
private:
	double rotate = 0;
public:
	RotationPhysics(double n);
	~RotationPhysics();
	virtual void update(GameObject* o, Uint32 time);
};

