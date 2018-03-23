#pragma once
#include"InputComponent.h"

class AccelerationInputComponent: public InputComponent
{
private:
	SDL_Keycode accelerate_, deccelerate_;
	float vel = 0.1;
	float decceleration = 1;
	const float maxVel = 10;
public:
	virtual void handleInput(GameObject* o, uint32_t Time,const SDL_Event& e);
	AccelerationInputComponent(double angle, SDL_Keycode right, SDL_Keycode left,
		SDL_Keycode accelerate, SDL_Keycode deccelerate);
	~AccelerationInputComponent();
};

