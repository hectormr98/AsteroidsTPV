#include "StarTrekBulletManager.h"



StarTrekBulletManager::StarTrekBulletManager(SDLGame* game):GameObject(game)
{
	
	bulletRenderer_ = FillRectRenderer();
	bulletPhysics_ = BasicMotionPhysics();
}


StarTrekBulletManager::~StarTrekBulletManager()
{
}

std::vector<Bullet*>& StarTrekBulletManager::getBullets() {
	return bullets_;
}

void StarTrekBulletManager::Shoot(Fighter* owner, Vector2D pos, Vector2D vel) {
	Bullet* son = getBullet();

	son->setPosition(pos);
	son->setVelocity(vel);
}

Bullet* StarTrekBulletManager::getBullet() {
	int i = 0;
	while (i < bullets_.size() && bullets_[i]->isActive())
		i++;
	if (i < bullets_.size()) {
		bullets_[i]->setActive(true);
		return bullets_[i];
	}
	else {
		Bullet* bu = new Bullet(game_);

		bu->addPhysicsComponent(&bulletPhysics_);
		bu->addRenderComponent(&bulletRenderer_);

		bullets_.push_back(bu);
		return bu;
	}
}

void StarTrekBulletManager::handleInput(Uint32 time, const SDL_Event& e) {}

void StarTrekBulletManager::render(Uint32 time) {
	for (int i = 0; i < bullets_.size(); i++)
		if (bullets_[i]->isActive())
			bullets_[i]->render(time);
}

void StarTrekBulletManager::update(Uint32 time) {
	for (int i = 0; i < bullets_.size(); i++) {
		if (bullets_[i]->isActive()) {
			bullets_[i]->update(time);
			if (isOutOfBounds(bullets_[i]))
				bullets_[i]->setActive(false);
		}
	}
}

bool StarTrekBulletManager::isOutOfBounds(GameObject* obj) {
	return (obj->getPosition().getX() < 0 || obj->getPosition().getX() > game_->getWindowWidth()
		|| obj->getPosition().getY() < 0 || obj->getPosition().getY() > game_->getWindowHeight());
}

void StarTrekBulletManager::receive(Message* msg) {

	Bullet* aux = static_cast<BulletAstroidCollision*>(msg)->bullet_;
	switch (msg->id_)
	{
	case ROUND_START:
		for (int i = 0; i < bullets_.size(); i++)
		{
			bullets_[i]->setActive(false);
		}
		break;

	case ROUND_OVER:
		for (int i = 0; i < bullets_.size(); i++)
		{
			bullets_[i]->setActive(false);
		}
		break;

	case BULLET_ASTROID_COLLISION:
		aux->setActive(false);
		break;

	case BULLET_FIGHTER_COLLISION:
		aux->setActive(false);
		break;

	case FIGHTER_SHOOT:
		Fighter* fighter = static_cast<FighterIsShooting*>(msg)->fighter_;
		Shoot(fighter, static_cast<FighterIsShooting*>(msg)->bulletPosition_, static_cast<FighterIsShooting*>(msg)->bulletVelocity_);
		break;
	}

}
