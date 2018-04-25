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

#include"GunInputComponent.h"



ExampleGame::ExampleGame() :
	SDLGame("Example Game", _WINDOW_WIDTH_, _WINDOW_HEIGHT_),
	gameManager_(this), bulletsManager_(this), fightersManager_(this,&bulletsManager_),
	astroidsManager_(this), bonus(this), collisionManager_(this, &astroidsManager_, &bulletsManager_, &fightersManager_, &bonus),
	soundManager_(this){
	initGame();
	exit_ = false;
}

ExampleGame::~ExampleGame() {
	closeGame();
}

void ExampleGame::initGame() {

	// hide cursor
	SDL_ShowCursor(0);

	collisionManager_.registerObserver(&gameManager_);
	collisionManager_.registerObserver(&astroidsManager_);
	collisionManager_.registerObserver(&bulletsManager_);
	collisionManager_.registerObserver(&fightersManager_);
	collisionManager_.registerObserver(&soundManager_);

	astroidsManager_.registerObserver(&gameManager_);

	gameManager_.registerObserver(&bulletsManager_);
	gameManager_.registerObserver(&fightersManager_);
	gameManager_.registerObserver(&astroidsManager_);
	gameManager_.registerObserver(&soundManager_);

	actors_.push_back(&collisionManager_);
	actors_.push_back(&bulletsManager_);
	actors_.push_back(&astroidsManager_);
	actors_.push_back(&fightersManager_);
	actors_.push_back(&gameManager_);


	gameManager_.registerObserver(&bonus);
	collisionManager_.registerObserver(&bonus);
	actors_.push_back(&bonus);
	gameManager_.send(&Message(ROUND_START));

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
	if (gameManager_.isRunning()) {
		for (GameObject* o : actors_) {
			o->update(time);
		}
	}
	else {
		system("cls");
		cout << "Pulsa cualquier boton para empezar" << endl;
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

