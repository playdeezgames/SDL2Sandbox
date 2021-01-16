#include "OptionsRenderer.h"
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"
#include <sstream>
OptionsRenderer::OptionsRenderer
	(
		SDL_Renderer* renderer, 
		const RomFontManager& romFontManager, 
		const OptionsState& state,
		const tggd::common::SoundManager& soundManager
	)
	: BaseRenderer(renderer, romFontManager)
	, state(state)
	, soundManager(soundManager)
{

}

void OptionsRenderer::Draw()
{
	int row = Constants::Board::ROWS / 2;
	GetRomFont().DrawCenteredText(GetMainRenderer(), row + -1, "Options", Constants::Color::MAGENTA);

	RenderItem(row + 1, "Go Back", OptionsState::BACK);
	if (soundManager.IsMuted())
	{
		RenderItem(row + 2, "Unmute", OptionsState::TOGGLE_MUTE);
	}
	else
	{
		RenderItem(row + 2, "Mute", OptionsState::TOGGLE_MUTE);
	}
	std::stringstream ss;
	ss << "SFX: " << soundManager.GetSfxVolume();
	RenderItem(row + 3, ss.str(), OptionsState::SFX_VOLUME);
	ss.str("");
	ss << "MUX: " << soundManager.GetMuxVolume();
	RenderItem(row + 4, ss.str(), OptionsState::MUX_VOLUME);
}

void OptionsRenderer::RenderItem(int row, const std::string& text, const OptionsState& optionsState)
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), row, text, (optionsState == state) ? (Constants::Color::CYAN) : (Constants::Color::BROWN));
}
