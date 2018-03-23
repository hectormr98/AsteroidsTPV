#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

#include "GameObject.h"

/*
 *
 */
class InputComponent {
private:
	double rotationAngle = 0;
	SDL_Keycode right_,
		left_;
public:
	//InputComponent() {};
	InputComponent(double angle, SDL_Keycode right, SDL_Keycode left);
	virtual ~InputComponent();
	virtual void handleInput(GameObject* o, Uint32 time, const SDL_Event& event);
};

#endif /* INPUTCOMPONENT_H_ */
