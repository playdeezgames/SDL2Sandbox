#include "AboutRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"

AboutRenderer::AboutRenderer(SDL_Renderer* rend, const RomFontManager& romFont)
	: BaseRenderer(rend, romFont)
{

}

void AboutRenderer::Draw()
{
	int row = Constants::Board::ROWS / 2;
	GetRomFont().DrawCenteredText(GetMainRenderer(), row - 2, "-=-About JetLag 2021-=-", Constants::Color::WHITE);
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 0, "Produced By: TheGrumpyGameDev", Constants::Color::MAGENTA);
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 2, "https://www.twitch.tv/thegrumpygamedev", Constants::Color::MAGENTA);
}