#include "TitleScreenRenderer.h"
SDL_Renderer* TitleScreenRenderer::GetMainRenderer() const
{
	return renderer;
}

TitleScreenRenderer::TitleScreenRenderer
(
	SDL_Renderer* rend
)
	: renderer(rend)
{

}

void TitleScreenRenderer::Draw()
{

}

