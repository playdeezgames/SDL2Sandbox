#pragma once
#include "BaseRenderer.h"
class AboutRenderer : public BaseRenderer
{
public:
	AboutRenderer(SDL_Renderer*);
	void Draw();
};

