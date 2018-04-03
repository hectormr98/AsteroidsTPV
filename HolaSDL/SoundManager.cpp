#include "SoundManager.h"



SoundManager::SoundManager(SDLGame* gueim)
{
	game = gueim;
	sound = new SoundEffect();
}


SoundManager::~SoundManager()
{
}

void SoundManager::receive(Message* msg)
{
	SoundEffect* sound2 = new SoundEffect();
	switch (msg->id_)
	{
	case FIGHTER_SHOOT:
		sound2->load("sound/GunShot.wav");
		sound2->play(1);
		break;
	case BULLET_CREATED:
		sound2->load("sound/GunShot.wav");
		sound2->play(1);
		break;
	case BULLET_ASTROID_COLLISION:
		sound->load("sound/explosion.wav");
		sound->play(1);
		break;
	case ASTROID_FIGHTER_COLLISION:
		sound2->load("sound/boooo.wav");
		sound2->play(1);
		break;
	case ROUND_START:
		sound->load("sound/imperial_march.wav");
		sound->play(1);
		break;
	case ROUND_OVER:
		break;
	}
}
