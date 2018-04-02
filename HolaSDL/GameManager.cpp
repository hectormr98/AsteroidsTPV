#include "GameManager.h"

GameManager::GameManager(SDLGame* game) : GameObject(game)
{
	
}


GameManager::~GameManager()
{
}

bool GameManager::isGameOver()const {
	return true;
}

int GameManager::getScore()const {
	return 0;
}

int GameManager::getLives()const {
	return 0;
}

bool GameManager::isRunning()const {
	return false;
}

void GameManager::setRunning(bool r) {

}

void GameManager::setBadge(bool b) {
	if (b) {
		badge.start(5);
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
			system("cls");
			cout << vidas << endl;
			send(&Message(BADGE_OFF));
			send(&Message(ROUND_START));
		}
		break;
	case BULLET_ASTROID_COLLISION:
		badgeCounter++;
		if(badgeCounter == 2)
			setBadge(true);
		break;
	case NO_MORE_ATROIDS:

		break;
	default:
		break;
	}
}

void GameManager::update(Uint32 time) {
	badge.update(this, time);
}
