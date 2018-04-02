#include "AsteroidManager.h"



AsteroidManager::AsteroidManager(SDLGame* game): GameObject(game)
{
	astroidImage_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Airplanes));
	circularPhysics_ = CircularMotionPhysics();
	rotationPhysics_ = RotationPhysics(2);
	bm = BasicMotionPhysics();
	initAsteroids();
}


AsteroidManager::~AsteroidManager()
{
}

void AsteroidManager::receive(Message* msg) {
	Asteroid* aux = static_cast<BulletAstroidCollision*>(msg)->astroid_;
	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		if (aux->getGeneration() > 1) {
			int random = rand() % 3 + 2;
			for (int i = 0; i < random; i++) {
				Asteroid* son = getAsteroid();
				son->setPosition(aux->getPosition());
				son->setDirection(Vector2D((rand() % 200 - 100) / 100, (rand() % 200 - 100) / 100));
				Vector2D auxVel = aux->getVelocity();
				auxVel.rotate(30 * (i- random/2));
				son->setVelocity(auxVel);
				son->setGeneration(aux->getGeneration() - 1);
				son->setWidth(son->getGeneration() * 15 + 10);
				son->setHeight(son->getGeneration() * 15 + 10);
			}
		}
		aux->setActive(false);
		break;
	case ROUND_START:
		initAsteroids();
		break;
	default:
		break;
	}
}

Asteroid* AsteroidManager::getAsteroid() {
	int i = 0;
	while (i < astroids_.size() && !astroids_[i]->isActive())
		i++;
	if (i < astroids_.size()) {
		astroids_[i]->setActive(true);
		return astroids_[i];
	}
	else {
		Asteroid* st = new Asteroid(game_);

		st->addPhysicsComponent(&rotationPhysics_);
		st->addPhysicsComponent(&circularPhysics_);
		st->addRenderComponent(&astroidImage_);

		st->addPhysicsComponent(&bm);

		astroids_.push_back(st);
		return st;
	}
}

void AsteroidManager::initAsteroids() {
	for (int i = 0; i < astroids_.size(); i++) {
		if (astroids_[i]->isActive())
			astroids_[i]->setActive(false);
	}
	int aux = rand() % 6 + 5;
	for (int i = 0; i < aux; i++) {
		int randPos = rand() % 2;
		if (i < astroids_.size()) {
			//random value in the limits of the window
			astroids_[i]->setPosition(Vector2D(randPos == 0 ? rand() % game_->getWindowWidth() : rand() % 50
				, randPos == 1 ? rand() % 50 : rand() % game_->getWindowHeight()));
			astroids_[i]->setDirection(Vector2D((rand() % 200 - 100) / 100, (rand() % 200 - 100) / 100));
			astroids_[i]->setVelocity(Vector2D((rand() % 200 - 100) / 100, (rand() % 200 - 100) / 100));
			int auxGen = rand() % 3 + 1;
			astroids_[i]->setGeneration(auxGen);
			astroids_[i]->setHeight(auxGen * 15 + 10);
			astroids_[i]->setWidth(auxGen * 15 + 10);
		}
		else {
			Asteroid* st = getAsteroid();
			//astroids_.push_back(getAsteroid());
			st->setPosition(Vector2D(randPos == 0 ? rand() % game_->getWindowWidth() : rand() % 50
				, randPos == 1 ? rand() % 50 : rand() % game_->getWindowHeight()));
			st->setDirection(Vector2D((rand() % 200 - 100) / 100, (rand() % 200 - 100) / 100));
			st->setVelocity(Vector2D((rand() % 200 - 100) / 100, (rand() % 200 - 100) / 100));
			int auxGen = rand() % 3 + 1;
			st->setGeneration(auxGen);
			st->setHeight(auxGen * 15 + 10);
			st->setWidth(auxGen * 15 + 10);
		}
	}
	numOfAsteroids_ = astroids_.size();
}

void AsteroidManager::handleInput(Uint32 time, const SDL_Event& e) {}

void AsteroidManager::update(Uint32 time) {
	for (int i = 0; i < astroids_.size(); i++) {
		if (astroids_[i]->isActive())
			astroids_[i]->update(time);
	}
}

void AsteroidManager::render(Uint32 time) {
	for (int i = 0; i < astroids_.size(); i++) {
		if (astroids_[i]->isActive())
			astroids_[i]->render(time);
	}
}