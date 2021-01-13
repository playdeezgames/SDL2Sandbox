#include "GameOverRenderer.h"
SDL_Renderer* GameOverRenderer::GetMainRenderer() const
{
	return renderer;
}

void GameOverRenderer::Draw()
{

}

GameOverRenderer::GameOverRenderer(SDL_Renderer* rend)
	: renderer(rend)
{

}