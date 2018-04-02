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

}

void GameManager::receive(Message* msg) {
	Message* toSend = nullptr;
	switch (msg->id_)
	{
	case ASTROID_FIGHTER_COLLISION:

		break;
	case BULLET_ASTROID_COLLISION:

		break;
	case NO_MORE_ATROIDS:

		break;
	default:
		break;
	}
}
