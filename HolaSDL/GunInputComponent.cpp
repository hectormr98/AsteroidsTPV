#include "GunInputComponent.h"



GunInputComponent::GunInputComponent(BulletsManager* bm, SDL_Keycode s, Uint8 shotsPerInterval, Uint32 timeInterval): InputComponent(0, NULL, NULL)
{
	manager = bm;
	activator = s;
	disponibleShots = shotsPerInterval;
	IntervalTime = timeInterval;
	auxShots = disponibleShots;
	timer = new Timer();
}


GunInputComponent::~GunInputComponent()
{
	manager = nullptr;
}

void GunInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& e) {
	timer->update();
	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == activator) {
			if (timer->TimeSinceTimerCreation >= IntervalTime) {
				auxShots = disponibleShots;
				timer->restart();
			}
			if(auxShots > 0)
			{
				auxShots--;
				Vector2D bulletPos = { o->getWidth() / 2, (o->getHeight() / 2) };
				Vector2D bulletDir = (o->getDirection() * o->getHeight() / 2);
				bulletDir.setX(-bulletDir.getX());
				Vector2D bulletVel = o->getDirection() * SDL_max(o->getVelocity().magnitude() * 2, 2.0);
				bulletVel.setX(-bulletVel.getX());

				Fighter* fighter = static_cast<Fighter*>(o);
				Message* mensaje = new FighterIsShooting(fighter, fighter->getPosition() + bulletPos + bulletDir, bulletVel);
				send(mensaje);
			}
		}
	}
}
