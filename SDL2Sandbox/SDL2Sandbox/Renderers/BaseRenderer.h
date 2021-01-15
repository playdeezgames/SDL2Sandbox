#pragma once
#include "..\Common\Application.h"
class BaseRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	BaseRenderer(SDL_Renderer*);
};

