#include "ExampleGame.h"
#include "DemoActor.h"
#include "Collisions.h"
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
	StarTrekBulletManager* bulletManager = new StarTrekBulletManager(this);
	actors_.push_back(bulletManager);
	FightersManager* fighter = new FightersManager(this, bulletManager);
	actors_.push_back(fighter);
	AsteroidManager* asteroids = new AsteroidManager(this);
	actors_.push_back(asteroids);
	

	/*airplanes_ = new GameComponent(this);
	airplanes_->setWidth(50);
	airplanes_->setHeight(50);
	airplanes_->setPosition(Vector2D(getWindowWidth() / 3, getWindowHeight() / 4 + getWindowHeight()/2));
	airplanes_->setVelocity(Vector2D(1, 0));
	airplanes_->setDirection(Vector2D(0, -1));

	renderComp_ = new ImageRenderer(getResources()->getImageTexture(Resources::Airplanes));
	airplanes_->addRenderComponent(renderComp_);
	inputComp_ = new AccelerationInputComponent(5, SDLK_a, SDLK_d, SDLK_w, SDLK_s);
	physicsComp_ = new BasicMotionPhysics();

	// choose either the filled rectangle or the image renderer
	//
	//	renderComp_ = new FillRectRenderer( { COLOR(0x11ff22ff) });
	//renderComp_ = new ImageRenderer( getResources()->getImageTexture(Resources::Star));

	airplanes_->addInputComponent(inputComp_);

	StarTrekBulletManager* illo = new StarTrekBulletManager(this);
	actors_.push_back(illo);
	inputComp_ = new GunInputComponent(illo, SDLK_SPACE, 5, 3);
	airplanes_->addInputComponent(inputComp_);

	airplanes_->addPhysicsComponent(physicsComp_);

	physicsComp_ = new CircularMotionPhysics();
	airplanes_->addPhysicsComponent(physicsComp_);
	//physicsComp_ = new RotationPhysics(5);
	//airplanes_->addPhysicsComponent(physicsComp_);
	actors_.push_back(airplanes_);*/
	

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

