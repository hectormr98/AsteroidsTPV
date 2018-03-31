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
	virtual void Shoot(Vector2D pos, Vector2D dir, Vector2D vel);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time ,const SDL_Event& e);

	SDLGame* getGame();

	StarWarsBulletManager(SDLGame* game);
	~StarWarsBulletManager();

	bool IsOutOfBounds(GameObject* object);
};

