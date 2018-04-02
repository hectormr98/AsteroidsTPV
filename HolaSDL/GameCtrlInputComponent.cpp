#include "GameCtrlInputComponent.h"
#include "GameManager.h"

GameCtrlInputComponent::GameCtrlInputComponent() : InputComponent(0,NULL, NULL) {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {

		// if any key pressed while not running, we choose a random velocity of the ball
		if (!gm->isRunning()) {
			gm->setRunning(true);
			// rest the score if the game is over
			if (gm->isGameOver()) {
				cout << gm->getScore();
				//gm->setRightScore(0);
			}
		}
	}

}
