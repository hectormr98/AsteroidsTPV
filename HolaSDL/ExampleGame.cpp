#include "ExampleGame.h"
#include "DemoActor.h"
//#include "Collisions.h"
#include "BasicKBCtrlComponent.h"
#include "BasicMotionPhysics.h"
#include "FillRectRenderer.h"
#include "ImageRenderer.h"
#include "AccelerationInputComponent.h"

#include"CircularMotionPhysics.h"
#include"RotationPhysics.h"

#include"StarWarsBulletManager.h"
#include"StarTrekBulletManager.h"
#include"GunInputComponent.h"
#include "FightersManager.h"
#include"AsteroidManager.h"
#include"CollisionsManager.h"
#include"GameManager.h"
#include "SoundManager.h"


ExampleGame::ExampleGame() :
		SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_) {
	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);
	GameManager* GM = new GameManager(this);

	StarTrekBulletManager* bulletManager = new StarTrekBulletManager(this);

	FightersManager* fighter = new FightersManager(this, bulletManager);

	AsteroidManager* asteroids = new AsteroidManager(this);

	CollisionsManager* coll = new CollisionsManager(this, asteroids, bulletManager, fighter);

	SoundManager* sound = new SoundManager(this);

	coll->registerObserver(GM);
	coll->registerObserver(asteroids);
	coll->registerObserver(bulletManager);
	coll->registerObserver(fighter);
	coll->registerObserver(sound);


	GM->registerObserver(bulletManager);
	GM->registerObserver(fighter);
	GM->registerObserver(asteroids);
	GM->registerObserver(sound);

	actors_.push_back(coll);
	actors_.push_back(bulletManager);
	actors_.push_back(fighter);
	actors_.push_back(asteroids);
	actors_.push_back(GM);


	GM->send(&Message(ROUND_START));

}

void ExampleGame::closeGame() {
	if (demoObj_ != nullptr)
		delete demoObj_;
	if (demoComp_ != nullptr)
		delete demoComp_;
	if (inputComp_ != nullptr)
		delete inputComp_;
	if (physicsComp_ != nullptr)
		delete physicsComp_;
	if (renderComp_ != nullptr)
		delete renderComp_;
}

void ExampleGame::start() {
	exit_ = false;
	while (!exit_) {
		Uint32 startTime = SDL_GetTicks();
		handleInput(startTime);
		update(startTime);
		render(startTime);
		Uint32 frameTime = SDL_GetTicks() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void ExampleGame::stop() {
	exit_ = true;
}

void ExampleGame::handleInput(Uint32 time) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				exit_ = true;
				break;
				// Pressing f to toggle fullscreen.
			case SDLK_f:
				int flags = SDL_GetWindowFlags(window_);
				if (flags & SDL_WINDOW_FULLSCREEN) {
					SDL_SetWindowFullscreen(window_, 0);
				} else {
					SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN);
				}
				break;
			}
		}
		for (GameObject* o : actors_) {
			o->handleInput(time, event);
		}
	}
}

void ExampleGame::update(Uint32 time) {
	for (GameObject* o : actors_) {
		o->update(time);
	}
}

void ExampleGame::render(Uint32 time) {
	SDL_SetRenderDrawColor(getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(getRenderer());

	for (GameObject* o : actors_) {
		o->render(time);
	}

	SDL_RenderPresent(getRenderer());
}

