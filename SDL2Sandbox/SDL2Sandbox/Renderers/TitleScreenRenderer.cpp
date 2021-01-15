#include "TitleScreenRenderer.h"
#include "..\Constants\Board.h"
#include "..\Constants\Color.h"
SDL_Renderer* TitleScreenRenderer::GetMainRenderer() const
{
	return renderer;
}

TitleScreenRenderer::TitleScreenRenderer
(
	SDL_Renderer* rend,
	const tggd::common::SoundManager& sndMan,
	const RomFontManager& romFont,
	const GameData& data
)
	: renderer(rend)
	, soundManager(sndMan)
	, romFontManager(romFont)
	, gameData(data)
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
	romFontManager.DrawCenteredText(GetMainRenderer(), row, text, (gameData.GetMainMenuItem() == item) ? (Constants::Color::CYAN) : (Constants::Color::BROWN));
}