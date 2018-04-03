#include "AsteroidManager.h"
#include"GameManager.h"
#include<ctime>

AsteroidManager::AsteroidManager(SDLGame* game): GameObject(game)
{
	astroidImage_ = ImageRenderer(game->getResources()->getImageTexture(Resources::Astroid));
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
			numOfAsteroids_ += random; //add the new sons
			for (int i = 0; i < random; i++) {
				Asteroid* son = getAsteroid();
				son->setPosition(aux->getPosition());
				son->setDirection(Vector2D(((double)(rand() % 200) - 100) / 100, ((double)(rand() % 200) - 100) / 100));
				Vector2D auxVel = aux->getVelocity();
				auxVel.rotate(30 * (i- random/2));
				son->setVelocity(auxVel);
				son->setGeneration(aux->getGeneration() - 1);
				son->setWidth(son->getGeneration() * 15 + 10);
				son->setHeight(son->getGeneration() * 15 + 10);
			}
		}
		aux->setActive(false);
  		numOfAsteroids_--; //rest the father who died
		if (numOfAsteroids_ <= 0) //end of the level
 			send(&Message(NO_MORE_ATROIDS));
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
	while (i < astroids_.size() && astroids_[i]->isActive())
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
	int aux = rand() % 6 + 1;

	for (int i = 0; i < aux; i++) {

		int randPos = rand() % 4;
		if (i < astroids_.size()) {
			//random value in the limits of the window
			switch (randPos)
			{
			case 0:
				astroids_[i]->setPosition(Vector2D(rand() % game_->getWindowWidth(), rand() % 50));
				break;
			case 1:
				astroids_[i]->setPosition(Vector2D(rand() % 50, rand() % game_->getWindowHeight()));
				break;
			case 2:
				astroids_[i]->setPosition(Vector2D(rand() % game_->getWindowWidth(), rand() % 50 - 100 + game_->getWindowHeight()));
				break;
			case 3:
				astroids_[i]->setPosition(Vector2D(rand() % 50 - 100 + game_->getWindowWidth(), rand() % game_->getWindowHeight()));
				break;
			default:
				break;
			}
			astroids_[i]->setDirection(Vector2D(((double)(rand() % 200) - 100) / 100, ((double)(rand() % 200) - 100) / 100));
			astroids_[i]->setVelocity(Vector2D(((double)(rand() % 200) - 100) / 100, ((double)(rand() % 200) - 100) / 100));
			int auxGen = rand() % 3 + 1;
			astroids_[i]->setGeneration(auxGen);
			astroids_[i]->setHeight(auxGen * 15 + 10);
			astroids_[i]->setWidth(auxGen * 15 + 10);
			astroids_[i]->setActive(true);
		}
		else {
			Asteroid* st = getAsteroid();
			switch (randPos)
			{
			case 0:
				st->setPosition(Vector2D(rand() % game_->getWindowWidth(), rand() % 50));
				break;
			case 1:
				st->setPosition(Vector2D(rand() % 50, rand() % game_->getWindowHeight()));
				break;
			case 2:
				st->setPosition(Vector2D(rand() % game_->getWindowWidth(), rand() % 50 - 100 + game_->getWindowHeight()));
				break;
			case 3:
				st->setPosition(Vector2D(rand() % 50 - 100 + game_->getWindowWidth(), rand() % game_->getWindowHeight()));
				break;
			default:
				break;
			}

			st->setDirection(Vector2D(((double)(rand() % 200) - 100) / 100, ((double)(rand() % 200) - 100) / 100));
			st->setVelocity(Vector2D(((double)(rand() % 200) - 100) / 100, ((double)(rand() % 200) - 100) / 100));

			int auxGen = rand() % 3 + 1;
			st->setGeneration(auxGen);
			st->setHeight(auxGen * 15 + 10);
			st->setWidth(auxGen * 15 + 10);
		}
	}
	numOfAsteroids_ = aux;
	
	//GameManager::setAsteroids(numOfAsteroids_);
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

std::vector<Asteroid*> AsteroidManager::getAsteroids() { return astroids_; };