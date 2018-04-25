#include "GameManager.h"

GameManager::GameManager(SDLGame* game) : GameObject(game)
{
	score = 0;
	
}


GameManager::~GameManager()
{
}

bool GameManager::isGameOver()const {
	return true;
}

int GameManager::getScore()const {
	return score;
}

int GameManager::getLives()const {
	return vidas;
}

bool GameManager::isRunning()const {
	return running;
}

void GameManager::setRunning(bool r) {
	running = r;
}

void GameManager::setBadge(bool b) {
	if (b) {
		badge.start(10);
		send(&Message(BADGE_ON));
	}
	else {
		send(&Message(BADGE_OFF));
		badgeCounter = 0;
	}
}

void GameManager::receive(Message* msg) {
	Message* toSend = nullptr;
	switch (msg->id_)
	{
	case ASTROID_FIGHTER_COLLISION:
		vidas--;
		if (vidas <= 0) {
			send(&Message(ROUND_OVER));
		}
		else {
			send(&Message(BADGE_OFF));
			send(&Message(ROUND_START));
			badgeCounter = 0;

		}
		setRunning(false);
		break;
	case BULLET_ASTROID_COLLISION:
		score++;
		badgeCounter++;
		if(badgeCounter == 4)
			setBadge(true);
		break;
	case NO_MORE_ATROIDS:
		if(vidas <=2)
			vidas++;
		ronda++;
		send(&Message(BADGE_OFF));
		send(&Message(ROUND_START));
		send(&Message(NO_MORE_ATROIDS));
		badgeCounter = 0;
		setRunning(false);
		break;
	case BONUS_OFF:
		if (vidas <= 2)
			vidas++;
		break;
	default:
		break;
	}
}

void GameManager::update(Uint32 time) {
	badge.update(this, time);
}

void GameManager::addScore(int i)
{
	//score++;
}
void GameManager::setAsteroids(int i)
{
	numAsteroids = i;
}

int GameManager::getRound() const{ return ronda; }

void GameManager::render(Uint32 time) {
	lifes.render(this, time);
	scoreRend.render(this, time);
}

void GameManager::handleInput(Uint32 time, const SDL_Event& e) {
	control.handleInput(this, time, e);
}