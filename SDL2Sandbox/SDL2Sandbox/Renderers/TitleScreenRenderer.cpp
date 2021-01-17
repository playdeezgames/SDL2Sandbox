#include "TitleScreenRenderer.h"
#include "..\Constants\Board.h"
#include "..\Constants\Color.h"
TitleScreenRenderer::TitleScreenRenderer
(
	SDL_Renderer* rend,
	const tggd::common::SoundManager& sndMan,
	const RomFontManager& romFont,
	const MainMenuItem& mainMenuItem
)
	: BaseRenderer(rend, romFont)
	, soundManager(sndMan)
	, mainMenuItem(mainMenuItem)
{

}

void TitleScreenRenderer::Draw()
{
	DrawMenuItem(Constants::Board::ROWS / 2 + 0, "Start!", MainMenuItem::PLAY);
	DrawMenuItem(Constants::Board::ROWS / 2 + 1, "Instructions", MainMenuItem::INSTRUCTIONS);
	DrawMenuItem(Constants::Board::ROWS / 2 + 2, "About", MainMenuItem::ABOUT);
	DrawMenuItem(Constants::Board::ROWS / 2 + 3, "Options", MainMenuItem::OPTIONS);
	DrawMenuItem(Constants::Board::ROWS / 2 + 4, "Quit", MainMenuItem::QUIT);
}

void TitleScreenRenderer::DrawMenuItem(int row, const std::string& text, const MainMenuItem& item) const
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), row, text, (mainMenuItem == item) ? (Constants::Color::CYAN) : (Constants::Color::BROWN));
}