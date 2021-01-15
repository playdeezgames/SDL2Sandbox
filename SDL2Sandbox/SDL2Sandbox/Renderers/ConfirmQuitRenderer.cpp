#include "ConfirmQuitRenderer.h"
ConfirmQuitRenderer::ConfirmQuitRenderer(SDL_Renderer* rend, const RomFontManager& romFont, const bool& conf)
	: BaseRenderer(rend, romFont)
	, confirm(conf)
{

}

void ConfirmQuitRenderer::Draw()
{

}