#include "ConfirmQuitRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"
ConfirmQuitRenderer::ConfirmQuitRenderer(SDL_Renderer* rend, const RomFontManager& romFont, const bool& conf)
	: BaseRenderer(rend, romFont)
	, confirm(conf)
{

}

void ConfirmQuitRenderer::Draw()
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::Board::ROWS / 2 + 0, "Do you really want to quit?", Constants::Color::RED);
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::Board::ROWS / 2 + 1, "No", (confirm) ? (Constants::Color::BROWN) : (Constants::Color::CYAN));
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::Board::ROWS / 2 + 2, "Yes", (confirm) ? (Constants::Color::CYAN) : (Constants::Color::BROWN));
}