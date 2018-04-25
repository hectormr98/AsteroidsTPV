#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsMamager):GameObject(game)
{
	sound = new SoundManager(game);
	fighter = new Fighter(game, 0);
	fighter->setWidth(50);
	fighter->setHeight(50);
	fighter->setPosition(Vector2D(game->getWindowWidth() / 2, game->getWindowHeight() / 2));
	fighter->setVelocity(Vector2D(0, 0));
	fighter->setDirection(Vector2D(0, -1));

	renderComp_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Airplanes));
	fighter->addRenderComponent(&renderComp_);
	circulrMotoionComp_ = CircularMotionPhysics();
	fighter->addPhysicsComponent(&circulrMotoionComp_);
	accelerationComp_ = new  AccelerationInputComponent(5, SDLK_a, SDLK_d, SDLK_w, SDLK_s);
	fighter->addInputComponent(accelerationComp_);
	
	physics = BasicMotionPhysics();
	fighter->addPhysicsComponent(&physics);

	gunComp1_ = new GunInputComponent(static_cast<BulletsManager*>(bulletsMamager), SDLK_SPACE, 5, 3);
	fighter->addInputComponent(gunComp1_);
	badge1_ = new GunInputComponent(static_cast<BulletsManager*>(bulletsMamager), SDLK_SPACE, 1000, 3);
	badge2_ = new GunInputComponent(static_cast<BulletsManager*>(bulletsMamager), SDLK_SPACE, 5, 3);
	badge3_ = new SixWaysGunInput(static_cast<BulletsManager*>(bulletsMamager), SDLK_SPACE, 5, 3);

	gunComp1_->registerObserver(bulletsMamager);
	badge1_->registerObserver(bulletsMamager);
	badge2_->registerObserver(bulletsMamager);
	badge3_->registerObserver(bulletsMamager);
	gunComp1_->registerObserver(sound);
	badge1_->registerObserver(sound);
	badge2_->registerObserver(sound);
	badge3_->registerObserver(sound);
}


FightersManager::~FightersManager()
{
}

void FightersManager::handleInput(Uint32 time, const SDL_Event& event)
{
	if(fighter->isActive())
		fighter->handleInput(time, event);
}
void FightersManager::update(Uint32 time)
{
	if (fighter->isActive()) {
		fighter->update(time);
	}
	fighter->badgeType = badgeType;
	fighter->badgeOn = badgeOn;
}
void FightersManager::render(Uint32 time)
{
	if(fighter->isActive())
		fighter->render(time);
}

Fighter* FightersManager::getFighter()
{
	return fighter;
}

void FightersManager::receive(Message* msg) {

	switch (msg->id_) 
	{
	case ROUND_START:
		fighter->setActive(true);
		fighter->setPosition(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
		fighter->setDirection(Vector2D(0, -1));
		fighter->setVelocity(Vector2D(0, 0));
		badgeType = 0;
			break;
	case ROUND_OVER:
		fighter->setActive(false);
		badgeType = 0;
			break;
	case BADGE_ON:
		badgeOn = true;
 		badgeType++;
		if (badgeType > maxBadges) badgeType = 1;
		fighter->delInputComponent(gunComp1_);
		fighter->delInputComponent(badge1_);
		fighter->delInputComponent(badge2_);
		fighter->delInputComponent(badge3_);
		fighter->delRenderComponent(&badgeRenderer_);

		if (badgeType == 1)
		{
			badgeRenderer_.changeTexture("images/badge.png");
			fighter->addInputComponent(badge1_);
		}
		else if (badgeType == 2)
		{
			badgeRenderer_.changeTexture("images/badge2.png");
			fighter->addInputComponent(badge2_);
		}
		else if (badgeType == 3)
		{
			badgeRenderer_.changeTexture("images/badge3.png");
			fighter->addInputComponent(badge3_);
		}


		fighter->addRenderComponent(&badgeRenderer_);
			break;
	case BADGE_OFF:
		badgeOn = false;
		fighter->delInputComponent(gunComp1_);
		fighter->delInputComponent(badge1_);
		fighter->delInputComponent(badge2_);
		fighter->delInputComponent(badge3_);

		fighter->delRenderComponent(&badgeRenderer_);
		fighter->addInputComponent(gunComp1_);
			break;
	}

}