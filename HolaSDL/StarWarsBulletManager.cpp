#include "StarWarsBulletManager.h"
#include"GameComponent.h"
#include"BasicMotionPhysics.h"
#include"FillRectRenderer.h"


StarWarsBulletManager::StarWarsBulletManager(SDLGame* gam) : BulletsManager(), GameObject(gam)
{
	game = gam;
}


StarWarsBulletManager::~StarWarsBulletManager()
{
}

void StarWarsBulletManager::Shoot(Vector2D IniPos, Vector2D IniDir, Vector2D IniVel) {
	GameComponent* comp = new GameComponent(game);
	comp->addPhysicsComponent(new BasicMotionPhysics());
	comp->addRenderComponent(new FillRectRenderer());
	comp->setHeight(5);
	comp->setWidth(5);

	Vector2D aux = IniVel;
	aux.setX(-IniVel.getX());

	comp->setVelocity(aux);
	comp->setDirection(IniDir);
	comp->setPosition(IniPos);

	bullets.push_back(comp);
}

void StarWarsBulletManager::update(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++) {
		if(bullets[i]->isActive())
		bullets[i]->update(time);
		if (bullets[i]->isActive() && IsOutOfBounds(bullets[i])) {
			bullets[i]->setActive(false);
		}
	}
}

void StarWarsBulletManager::render(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++)
		if(bullets[i]->isActive())
			bullets[i]->render(time);
}

bool StarWarsBulletManager::IsOutOfBounds(GameObject* obj) {
	return (obj->getPosition().getX() < 0 || obj->getPosition().getX() > game->getWindowWidth()
		|| obj->getPosition().getY() < 0 || obj->getPosition().getY() > game->getWindowHeight());
}

void StarWarsBulletManager::handleInput(Uint32 time, const SDL_Event& e) {}

SDLGame* StarWarsBulletManager::getGame() { return game; }