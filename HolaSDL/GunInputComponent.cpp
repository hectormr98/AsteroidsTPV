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

void GunInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == activator) {
			std::cout << 1 << std::endl;
			Vector2D bulletPos = { o->getWidth() / 2, (o->getHeight() / 2) };
			Vector2D bulletDir = (o->getDirection() * o->getHeight() / 2);
			Vector2D bulletVel = o->getDirection() * SDL_max(o->getVelocity().magnitude() * 2, 2.0);
			
			static_cast<StarWarsBulletManager*>(manager)->Shoot(o->getPosition() + bulletPos + bulletDir, o->getDirection(), bulletVel);
		}
	}
}
