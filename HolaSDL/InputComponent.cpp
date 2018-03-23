#include "InputComponent.h"

InputComponent::InputComponent(double angle, SDL_Keycode right, SDL_Keycode left) {
	// TODO Auto-generated constructor stub
	rotationAngle = angle;
	right_ = right;
	left_ = left;
}

InputComponent::~InputComponent() {
	// TODO Auto-generated destructor stub
}

void InputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& e) {
	if (e.key.keysym.sym == right_) {
		Vector2D aux = o->getDirection();
		aux.rotate(rotationAngle);
		o->setDirection(aux);
	}
	else if (e.key.keysym.sym == left_) {
		Vector2D aux = o->getDirection();
		aux.rotate(-rotationAngle);
		o->setDirection(aux);
	}
}

