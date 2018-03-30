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

void StarWarsBulletManager::Shoot() {
	GameComponent* comp = new GameComponent(game);
	comp->addPhysicsComponent(new BasicMotionPhysics());
	SDL_Surface *s; 
	s = SDL_CreateRGBSurface(0, width_, height_, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));

	//comp->addRenderComponent(new FillRectRenderer(s));
	comp->addRenderComponent(new FillRectRenderer());
	comp->setHeight(5);
	comp->setWidth(5);
	comp->setVelocity(Vector2D(1, 0.5));
	bullets.push_back(comp);
}

void StarWarsBulletManager::update(Uint32 time) {
	for (int i = 0; i < bullets.size(); i++) {
		if(bullets[i]->isActive())
		bullets[i]->update(time);
		if (bullets[i]->isActive() && IsOutOfBounds(bullets[i]))
			bullets[i]->setActive(false);
	}
	//bullets[0]->setPosition(Vector2D(game->getWindowWidth() / 2, game->getWindowHeight() / 2));
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