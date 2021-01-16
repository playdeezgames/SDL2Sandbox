#include "InstructionsRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"
InstructionsRenderer::InstructionsRenderer(SDL_Renderer* rend, const RomFontManager& romFont)
	: BaseRenderer(rend, romFont)
{

}

void InstructionsRenderer::Draw()
{
	int row = Constants::Board::ROWS / 2;
	GetRomFont().DrawCenteredText(GetMainRenderer(), row - 3, "-=-Instructions-=-", Constants::Color::WHITE);

	GetRomFont().DrawCenteredText(GetMainRenderer(), row - 1, "Keyboard Controls:", Constants::Color::CYAN);
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 0, "Arrows, Space, Esc", Constants::Color::MAGENTA);

	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 2, "Game Controller:", Constants::Color::CYAN);
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 3, "LStick, (A), (Back)", Constants::Color::MAGENTA);
}