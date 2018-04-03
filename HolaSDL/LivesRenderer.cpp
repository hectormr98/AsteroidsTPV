#include "LivesRenderer.h"
#include"GameManager.h"


LivesRenderer::LivesRenderer()
{
}


LivesRenderer::~LivesRenderer()
{
}

void LivesRenderer::render(GameObject* o, Uint32 time) {
	GameManager* gm = static_cast<GameManager*>(o);

	SDLGame* game = gm->getGame();
	SDL_Rect destRect;
	destRect.w = destRect.h = 25;
	destRect.y = 25;
	Texture* text = new Texture(game->getRenderer(), "images/life.png");
	for (int i = 0; i < gm->getLives(); i++) {
		destRect.x = 25 + i * 50;
		text->render(game->getRenderer(), destRect, 10);
	}
}
