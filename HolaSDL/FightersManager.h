#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "CircularMotionPhysics.h"
#include "ImageRenderer.h"
#include "AccelerationInputComponent.h"
#include "GunInputComponent.h"
#include"StarTrekBulletManager.h"
#include "SoundManager.h"


#include"BasicMotionPhysics.h"
//#include "RotationInputComp"
//#include "BadgeRenderer"



class FightersManager : public GameObject, public Observer {
public:
	FightersManager(SDLGame* game, Observer* bulletsMamager);
	virtual ~FightersManager();
	virtual void handleInput(Uint32 time, const SDL_Event& event);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	Fighter* getFighter();
	virtual void receive(Message* msg);
private:
	Fighter* fighter = nullptr;
	CircularMotionPhysics circulrMotoionComp_;
	
	BasicMotionPhysics physics;

	AccelerationInputComponent* accelerationComp_ = nullptr;
	ImageRenderer renderComp_ = nullptr;
	//RotationInputComp rotationComp_;
	GunInputComponent* gunComp1_ = nullptr;
	GunInputComponent* gunComp2_ = nullptr;
	SoundManager* sound;
	//BadgeRenderer badgeRenderer_;
};

