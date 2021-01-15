#include "BaseRenderer.h"
SDL_Renderer* BaseRenderer::GetMainRenderer() const
{
	return renderer;
}
BaseRenderer::BaseRenderer(SDL_Renderer* rend)
	: renderer(rend)
{
}

