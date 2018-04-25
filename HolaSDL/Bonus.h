#pragma once
#include "Container.h"
#include "BasicMotionPhysics.h"
#include "Timer.h"
#include "RenderComponent.h"
#include "RotationPhysics.h"
#include "ImageRenderer.h"
#include "Messages.h"
#include "Observer.h"
class Bonus : public Container, public Observer
{
public:
	Bonus(SDLGame* game);
	~Bonus();
	virtual void update(Uint32 time);
private:
	Timer* timer;
	RotationPhysics* rot;
	float time = 3;
	ImageRenderer ren = nullptr;
	void changePos();

protected:
	virtual void render() {};
	virtual void hanndleEvents() {};
	virtual void receive(Message* msg);
};

