#pragma once
#include"Container.h"
#include"Observable.h"
#include"Observer.h"

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

private:

};

