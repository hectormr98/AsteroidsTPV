#include "GunInputComponent.h"



GunInputComponent::GunInputComponent(BulletsManager* bm, SDL_Keycode s): InputComponent(0, NULL, NULL)
{
	manager = bm;
	activator = s;
}


GunInputComponent::~GunInputComponent()
{
	manager = nullptr;
}

void GunInputComponent::handleInput(Uint32 time, const SDL_Event& e) {
	if (e.key.keysym.sym == activator){

		static_cast<StarWarsBulletManager*>(manager)->Shoot();
	}
}
