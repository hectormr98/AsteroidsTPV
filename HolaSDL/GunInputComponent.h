#pragma once
#include"InputComponent.h"
#include"StarWarsBulletManager.h"

class GunInputComponent: public InputComponent
{
protected:
	BulletsManager* manager;
	SDL_Keycode activator;
public:
	GunInputComponent(BulletsManager* bm, SDL_Keycode s);
	~GunInputComponent();
	virtual void handleInput(GameObject* o,Uint32 time, const SDL_Event& e);
};

