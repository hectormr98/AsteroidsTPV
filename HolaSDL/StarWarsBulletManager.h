#pragma once
#include"GameObject.h"
#include"BulletsManager.h"


class StarWarsBulletManager : public GameObject, public BulletsManager
{
private:
	SDLGame* game;
protected:
	std::vector<GameObject*> bullets;
public:
	virtual void Shoot();
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time ,const SDL_Event& e);
	StarWarsBulletManager(SDLGame* game);
	~StarWarsBulletManager();

	bool IsOutOfBounds(GameObject* object);
};

