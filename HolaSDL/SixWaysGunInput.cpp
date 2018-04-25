#include "SixWaysGunInput.h"



SixWaysGunInput::SixWaysGunInput(BulletsManager* bm, SDL_Keycode s, Uint8 shotsPerInterval, Uint32 timeInterval) : InputComponent(0, NULL, NULL)
{
	manager = bm;
	activator = s;
	disponibleShots = shotsPerInterval;
	IntervalTime = timeInterval;
	auxShots = disponibleShots;
	timer = new Timer();
}


SixWaysGunInput::~SixWaysGunInput()
{
	manager = nullptr;
}

void SixWaysGunInput::handleInput(GameObject* o, Uint32 time, const SDL_Event& e) {
	timer->update();
	if (e.type == SDL_KEYDOWN) {

		if (e.key.keysym.sym == activator) {
			if (timer->TimeSinceTimerCreation >= IntervalTime) {
				auxShots = disponibleShots;
				timer->restart();
			}
			if (auxShots > 0)
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
					Vector2D aux = bulletVel;
					Vector2D auxPos = (fighter->getPosition() + bulletPos + bulletDir) -
						(fighter->getPosition() + Vector2D{ fighter->getWidth() / 2, fighter->getHeight() / 2 });
					for (int i = 1; i < 6; i++)
					{
						aux.rotate(60);
						auxPos.rotate(60);
						mensaje = new FighterIsShooting(fighter, auxPos + fighter->getPosition() + Vector2D{ fighter->getWidth() / 2, fighter->getHeight() / 2 },
							aux);
						send(mensaje);
					}
			}
		}
	}
}
