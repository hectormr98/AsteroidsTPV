#pragma once
#include "Observer.h"
#include "sdl_includes.h"
#include "SoundEffect.h"

class SoundManager: public Observer
{
public:
	SoundManager(SDLGame* gueim);
	virtual void receive(Message* msg);
	virtual ~SoundManager();

private:
	SDLGame* game;
	SoundEffect* sound;
};

