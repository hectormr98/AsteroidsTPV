#include "CollisionsManager.h"
#include"Collisions.h"


CollisionsManager::CollisionsManager(SDLGame* game, AsteroidManager* stm, BulletsManager* bm, FightersManager* ft):GameObject(game), Observable()
{
	asteroidManager = stm;
	bulletsManager = bm;
	fighterManager = ft;
}


CollisionsManager::~CollisionsManager()
{
}

void CollisionsManager::handleInput(Uint32 time, const SDL_Event& e){}

void CollisionsManager::render(Uint32 time){}

void CollisionsManager::update(Uint32 time) {
	Fighter* fighter = fighterManager->getFighter();
	vector<Bullet*> bullets = bulletsManager->getBullets();
	vector<Asteroid*> asteroids = asteroidManager->getAsteroids();

	//fighter with asteroids
	for (int i = 0; i < asteroids.size(); i++) {
		if (Collisions::collidesWithRotation(fighter, asteroids[i]))
			//send message
			;
	}

	//bullets with asteroids
	for (int i = 0; i < asteroids.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (Collisions::collidesWithRotation(bullets[j], asteroids[i]))
				//send message
				;
		}
	}
}
