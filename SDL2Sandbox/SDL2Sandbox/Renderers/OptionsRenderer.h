#pragma once
#include "BaseRenderer.h"
class OptionsRenderer : public BaseRenderer
{
public:
	OptionsRenderer(SDL_Renderer*);
	void Draw();
};

