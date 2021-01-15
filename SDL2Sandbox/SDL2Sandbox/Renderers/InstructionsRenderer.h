#pragma once
#include "BaseRenderer.h"
class InstructionsRenderer : public BaseRenderer
{
public:
	InstructionsRenderer(SDL_Renderer*);
	void Draw();
};

