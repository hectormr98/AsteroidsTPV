#include "AccelerationInputComponent.h"



AccelerationInputComponent::AccelerationInputComponent(double angle, SDL_Keycode right, SDL_Keycode left,
	SDL_Keycode accelerate, SDL_Keycode deccelerate)			: InputComponent(angle, right, left)
{
	accelerate_ = accelerate;
	deccelerate_ = deccelerate;
}


AccelerationInputComponent::~AccelerationInputComponent()
{
}

void AccelerationInputComponent::handleInput(GameObject* o, uint32_t Time,const SDL_Event& e) {
	Vector2D velocity = o->getVelocity();

	if (e.type == SDL_KEYDOWN) {
		Vector2D aux = o->getDirection();
		if (e.key.keysym.sym == accelerate_) {

			decceleration = 1;
			aux.setX(-aux.getX());
			if (sqrt(pow(o->getVelocity().getX(), 2) + pow(o->getVelocity().getY(), 2)) > maxVel) {
				o->setVelocity(o->getVelocity()*0.9f);
			}

			//velocity.set(aux*vel);
		}
		else if (e.key.keysym.sym == deccelerate_) {
			if(decceleration>0)
			decceleration -= 0.01f;
			aux.set(0, 0);
		}
		else {
			aux.set(0, 0);
		}
		InputComponent::handleInput(o, Time, e);

		velocity = o->getVelocity() + aux*vel;
		o->setVelocity(velocity*decceleration);
	}
}
