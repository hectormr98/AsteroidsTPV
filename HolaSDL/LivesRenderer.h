#pragma once
#include"RenderComponent.h"

class LivesRenderer:public RenderComponent
{
public:
	LivesRenderer();
	~LivesRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

