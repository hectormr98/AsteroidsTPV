#pragma once
#include"InputComponent.h"
#include"StarWarsBulletManager.h"
#include"StarTrekBulletManager.h"
#include "Timer.h"

class SixWaysGunInput : public InputComponent, public Observable
{
protected:
	BulletsManager* manager;
	SDL_Keycode activator;
public:
	SixWaysGunInput(BulletsManager* bm, SDL_Keycode s, Uint8 shotsPerInterval, Uint32 timeInterval);
	~SixWaysGunInput();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& e);
private:
	Uint8 disponibleShots;
	Uint32 IntervalTime;
	float auxInterval;
	int auxShots;

	Timer* timer;
};

