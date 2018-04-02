#include "FightersManager.h"



FightersManager::FightersManager(SDLGame* game, Observer* bulletsMamager):GameObject(game)
{
	fighter = new Fighter(game, 0);
	fighter->setWidth(50);
	fighter->setHeight(50);
	fighter->setPosition(Vector2D(game->getWindowWidth() / 3, game->getWindowHeight() / 4 + game->getWindowHeight() / 2));
	fighter->setVelocity(Vector2D(0, 0));
	fighter->setDirection(Vector2D(0, -1));

	renderComp_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid));
	fighter->addRenderComponent(&renderComp_);
	circulrMotoionComp_ = CircularMotionPhysics();
	fighter->addPhysicsComponent(&circulrMotoionComp_);
	accelerationComp_ = new AccelerationInputComponent(5, SDLK_a, SDLK_d, SDLK_w, SDLK_s);
	fighter->addInputComponent(accelerationComp_);

	StarTrekBulletManager* illo = new StarTrekBulletManager(game);
	gunComp1_ = new GunInputComponent(illo, SDLK_SPACE, 5, 3);
	fighter->addInputComponent(gunComp1_);
	gunComp2_ = new GunInputComponent(illo, SDLK_SPACE, 1000, 3);
}


FightersManager::~FightersManager()
{
}

void FightersManager::handleInput(Uint32 time, const SDL_Event& event)
{
	fighter->handleInput(time, event);
}
void FightersManager::update(Uint32 time)
{
	fighter->update(time);
	cout << fighter->getPosition();
	system("cls");
}
void FightersManager::render(Uint32 time)
{
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
			break;
	case ROUND_OVER:
		fighter->setActive(false);
			break;
	case BADGE_ON:
		fighter->delInputComponent(gunComp1_);
		fighter->addInputComponent(gunComp2_);
		//fighter->addRenderComponent(badgeRenderer);
			break;
	case BADGE_OFF:
		fighter->delInputComponent(gunComp2_);
		fighter->addInputComponent(gunComp1_);
		//fighter->delRenderComponent(badgeRenderer);
			break;
	}

}