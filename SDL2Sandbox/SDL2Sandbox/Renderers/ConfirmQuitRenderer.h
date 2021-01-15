#pragma once
#include "BaseRenderer.h"
class ConfirmQuitRenderer : public BaseRenderer
{
public:
	ConfirmQuitRenderer(SDL_Renderer*);
	void Draw();
};

