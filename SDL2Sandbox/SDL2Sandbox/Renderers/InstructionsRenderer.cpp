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
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 0, "Instructions", Constants::Color::WHITE);
}