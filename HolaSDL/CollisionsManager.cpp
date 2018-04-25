#include "CollisionsManager.h"
#include"Collisions.h"
#include "GameManager.h"


CollisionsManager::CollisionsManager(SDLGame* game, AsteroidManager* stm, BulletsManager* bm, FightersManager* ft, Bonus* bon):GameObject(game), Observable()
{
	asteroidManager = stm;
	bulletsManager = bm;
	fighterManager = ft;
	bonus = bon;
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
		if (asteroids[i]->isActive()) {
			if (Collisions::collidesWithRotation(fighter, asteroids[i])) {
				Message* mensaje = new AstroidFighterCollision(asteroids[i], fighter);
				send(mensaje);
			}
		}
	}
	//bullets with asteroids
	for (int i = 0; i < asteroids.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (bullets[j]->isActive() && asteroids[i]->isActive()) {
				if (Collisions::collidesWithRotation(bullets[j], asteroids[i])) {
					Message* mensaje = new BulletAstroidCollision(bullets[j], asteroids[i]);
					send(mensaje);
				}
			}
				
		}
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (Collisions::collidesWithRotation(bullets[i], bonus))
		{
			send(new Message(BONUS_OFF));
		}
	}
}
