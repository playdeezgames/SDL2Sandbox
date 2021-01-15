#include "GameOverRenderer.h"
#include "..\Constants\UI.h"
#include "..\Constants\Color.h"
void GameOverRenderer::Draw()
{
	DrawHints();
}

GameOverRenderer::GameOverRenderer
	(
		SDL_Renderer* rend, 
		const tggd::common::SoundManager& sndMan, 
		const RomFontManager& romFont, 
		const GameData& data
	)
	: BaseRenderer(rend, romFont)
	, soundManager(sndMan)
	, gameData(data)
{
}

void GameOverRenderer::DrawMuteHint()
{
	if (soundManager.IsMuted())
	{
		GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::UNMUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
	else
	{
		GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::MUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
}

void GameOverRenderer::DrawStartHint()
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::UI::START_MESSAGE_ROW, Constants::UI::START_HINT_TEXT, Constants::Color::MAGENTA);
}

void GameOverRenderer::DrawHints()
{
	if (gameData.GetGameState() == GameState::GAME_OVER)
	{
		DrawMuteHint();
		DrawStartHint();
	}
}
