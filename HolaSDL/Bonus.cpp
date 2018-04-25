#include "Bonus.h"



Bonus::Bonus(SDLGame* game) : Container(game)
{
	ren = ImageRenderer(game->getResources()->getImageTexture(Resources::Star));
	addRenderComponent(&ren);
	timer = new Timer();
	setActive(true);
	setHeight(50);
	setWidth(50);
	changePos();
	rot = new RotationPhysics(2);
	addPhysicsComponent(new BasicMotionPhysics());
	addPhysicsComponent(rot);
}


Bonus::~Bonus()
{
}

void Bonus::update(Uint32 times)
{
	timer->update();
	if (timer->TimeSinceTimerCreation >= time)
	{
		changePos();
		timer->restart();
	}
	rot->update(this, times);
}

void Bonus::changePos()
{
	int ranX = rand() % game_->getWindowWidth();
	int ranY = rand() % game_->getWindowHeight();
	setPosition({ double(ranX), double(ranY) });
}


void Bonus::receive(Message* msg)
{
	switch (msg->id_)
	{
	case NO_MORE_ATROIDS:
		setActive(true);
		changePos();
		addRenderComponent(&ren);

		break;
	case ROUND_OVER:
		delRenderComponent(&ren);
		setActive(false);
		break;
	case BONUS_OFF:
		delRenderComponent(&ren);
		setActive(false);
		break;
	}
}
