#include "OptionsRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"
OptionsRenderer::OptionsRenderer(SDL_Renderer* renderer, const RomFontManager& romFontManager, const OptionsState& state)
	: BaseRenderer(renderer, romFontManager)
	, state(state)
{

}

void OptionsRenderer::Draw()
{
	int row = Constants::Board::ROWS / 2;
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + 0, "Options", Constants::Color::MAGENTA);

	RenderItem(row + 1, "Go Back", OptionsState::BACK);
	RenderItem(row + 2, "Mute", OptionsState::TOGGLE_MUTE);
	RenderItem(row + 3, "SFX", OptionsState::SFX_VOLUME);
	RenderItem(row + 4, "MUX", OptionsState::MUX_VOLUME);
}

void OptionsRenderer::RenderItem(int row, const std::string& text, const OptionsState& optionsState)
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), row, text, (optionsState == state) ? (Constants::Color::CYAN) : (Constants::Color::BROWN));
}
