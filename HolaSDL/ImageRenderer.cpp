#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Texture* image) : image_(image) {
}

ImageRenderer::~ImageRenderer() {
}

void ImageRenderer::render(GameObject* o, Uint32 time) {
	double angle = o->getDirection().angle(Vector2D(0, -1));

	SDL_Rect rect
			RECT(o->getPosition().getX(), o->getPosition().getY(),
					o->getWidth(), o->getHeight());
	SDL_Rect* srcRect = new SDL_Rect();
	srcRect->x = 796;
	srcRect->y = 104;
	srcRect->w = 340;
	srcRect->h = 210;
	image_->render(o->getGame()->getRenderer(), rect, angle, srcRect);	
}