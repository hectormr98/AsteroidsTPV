#pragma once
#include"Container.h"
#include"Observable.h"
#include"Observer.h"
#include"BadgeTimer.h"

class GameManager : public GameObject, public Observable, public Observer
{
public:
	GameManager(SDLGame* game);
	virtual ~GameManager();

	bool isGameOver() const;
	int getLives() const;
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const;
	void setBadge(bool b);
	virtual void receive(Message* msg);

	void addScore(int i);
	void setAsteroids(int i);

	virtual void update(Uint32 time);
	virtual void render(Uint32 time) {};
	virtual void handleInput(Uint32 time, const SDL_Event& e) {};

private:
	int vidas = 3,
		badgeCounter = 0;
	int score;
	int numAsteroids;
	BadgeTimer badge;
};

