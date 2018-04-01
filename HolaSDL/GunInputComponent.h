#pragma once
#include"InputComponent.h"
#include"StarWarsBulletManager.h"
#include "Timer.h"

class GunInputComponent: public InputComponent
{
protected:
	BulletsManager* manager;
	SDL_Keycode activator;
public:
	GunInputComponent(BulletsManager* bm, SDL_Keycode s, Uint8 shotsPerInterval, Uint32 timeInterval);
	~GunInputComponent();
	virtual void handleInput(GameObject* o,Uint32 time, const SDL_Event& e);
private:
	Uint8 disponibleShots;
	Uint32 IntervalTime;
	float auxInterval;
	int auxShots;

	Timer* timer;
};

