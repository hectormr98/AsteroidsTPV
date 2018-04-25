#include "SoundManager.h"



SoundManager::SoundManager(SDLGame* gueim)
{
	game = gueim;
	sound = new SoundEffect();
	sound->load("sound/imperial_march.wav");
	sound2 = new SoundEffect();
	sound2->load("sound/GunShot.wav");
}


SoundManager::~SoundManager()
{
}

void SoundManager::receive(Message* msg)
{

	switch (msg->id_)
	{
	case FIGHTER_SHOOT:

		sound2->play(1);
		break;
	case BULLET_CREATED:
		sound2->play(1);
		break;
	case BULLET_ASTROID_COLLISION:
		sound->play(1);
		break;
	case ASTROID_FIGHTER_COLLISION:
		sound2->play(1);
		break;
	case ROUND_START:

		sound->play(1);
		break;
	case ROUND_OVER:
		break;
	}
}
