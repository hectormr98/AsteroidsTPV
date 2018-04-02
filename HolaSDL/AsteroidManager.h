#pragma once
#include"GameObject.h"
#include"Observer.h"
#include"Observable.h"
#include"Asteroid.h"
#include"ImageRenderer.h"
#include"RotationPhysics.h"
#include"CircularMotionPhysics.h"

#include"BasicMotionPhysics.h"

class AsteroidManager:public GameObject, public Observer, public Observable
{
public:
	AsteroidManager(SDLGame* game);
	~AsteroidManager();

	virtual void handleInput(Uint32 time, const SDL_Event& e);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	//virtual std::vector<Asteroid*>& getAsteroids();
	virtual void receive(Message* msg);
private:
	vector<Asteroid*> astroids_;

	int numOfAsteroids_;
	ImageRenderer astroidImage_ = nullptr;

	BasicMotionPhysics bm;

	CircularMotionPhysics circularPhysics_;
	RotationPhysics rotationPhysics_ = RotationPhysics(2);

	Asteroid* getAsteroid();	
	void initAsteroids();

};

