#include "BaseRenderer.h"
SDL_Renderer* BaseRenderer::GetMainRenderer() const
{
	return renderer;
}
BaseRenderer::BaseRenderer(SDL_Renderer* rend, const RomFontManager& romFont)
	: renderer(rend)
	, romFontManager(romFont)
{
}

const RomFontManager& BaseRenderer::GetRomFont() const
{
	return romFontManager;
}

