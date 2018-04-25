#pragma once
#include"GameObject.h"
#include"BulletsManager.h"
#include"FillRectRenderer.h"
#include"BasicMotionPhysics.h"

class StarTrekBulletManager:public GameObject, public BulletsManager
{
public:
	StarTrekBulletManager(SDLGame* game);
	~StarTrekBulletManager();

	virtual void handleInput(Uint32 time, const SDL_Event& e);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);

	virtual std::vector<Bullet*>& getBullets();
private:
	Bullet* getBullet(); //analogo a getAsteroid
	virtual void receive(Message* msg);
	virtual void Shoot(Fighter* owner, Vector2D position, Vector2D vel);

	std::vector<Bullet*> bullets_;
	FillRectRenderer bulletRenderer_;
	BasicMotionPhysics bulletPhysics_;

	bool isOutOfBounds(GameObject* o);

	int badgeType = 0;
	bool badgeOn = false;
};

