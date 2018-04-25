#include "BadgeRenderer.h"



BadgeRenderer::BadgeRenderer()
{
}


BadgeRenderer::~BadgeRenderer()
{
}

void BadgeRenderer::changeTexture(string file)
{
	filename = file;
}
void BadgeRenderer::render(GameObject* o, Uint32 time) {
	SDLGame* game = o->getGame();

	Texture* text = new Texture(game->getRenderer(), filename);
	SDL_Rect destRect;
	destRect.w = destRect.h = 50;
	destRect.y = 25;
	destRect.x = game->getWindowWidth() - 25 - destRect.w;

	text->render(game->getRenderer(), destRect, 10);
}
