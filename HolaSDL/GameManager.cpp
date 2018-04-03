#include "GameManager.h"

GameManager::GameManager(SDLGame* game) : GameObject(game)
{
	score = 0;
	cout << "ROUND:" + to_string(ronda) << endl;
	cout << "Lifes: " + to_string(vidas) << endl;
	
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
			cout << "ROUND:" +to_string( ronda) << endl;
			cout << "Lifes: "+ to_string(vidas) << endl;
			send(&Message(BADGE_OFF));
			send(&Message(ROUND_START));
		}
		break;
	case BULLET_ASTROID_COLLISION:
		score++;
		badgeCounter++;
		if(badgeCounter == 2)
			setBadge(true);
		break;
	case NO_MORE_ATROIDS:
		if(vidas <=2)
			vidas++;
		ronda++;
		system("cls");
		cout << "ROUND:" + to_string(ronda) << endl;
		cout << "Lifes: " + to_string(vidas) << endl;
		send(&Message(BADGE_OFF));
		send(&Message(ROUND_START));
		break;
	default:
		break;
	}
}

void GameManager::update(Uint32 time) {
	badge.update(this, time);
	/*if (score >= numAsteroids)
	{
		receive(&Message(NO_MORE_ATROIDS));
	}
	*/
}

void GameManager::addScore(int i)
{
	//score++;
}
void GameManager::setAsteroids(int i)
{
	numAsteroids = i;
}

void GameManager::render(Uint32 time) {
	lifes.render(this, time);
	scoreRend.render(this, time);
}