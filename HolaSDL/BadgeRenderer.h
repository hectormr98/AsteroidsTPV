#pragma once
#include"RenderComponent.h"
#include <string>
#include <iostream>

using namespace std;
class BadgeRenderer : public RenderComponent
{
public:
	BadgeRenderer();
	~BadgeRenderer();
	virtual void render(GameObject* o, Uint32 time);
	void changeTexture(string file);
private:
	string filename;
};

