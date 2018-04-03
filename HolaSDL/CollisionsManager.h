#pragma once
#include"Observable.h"
#include"GameObject.h"
#include"BulletsManager.h"
#include"AsteroidManager.h"
#include"FightersManager.h"

class CollisionsManager: public GameObject, public Observable	
{
public:
	CollisionsManager(SDLGame* game) :GameObject(game) {};
	CollisionsManager(SDLGame* game, 
						AsteroidManager* stm,
						BulletsManager* bum,
						FightersManager* ftm);
	virtual ~CollisionsManager();

	virtual void handleInput(Uint32 time, const SDL_Event& e);
	virtual void render(Uint32 time);
	virtual void update(Uint32 time);
private:
	BulletsManager* bulletsManager;
	AsteroidManager* asteroidManager;
	FightersManager* fighterManager;
};

