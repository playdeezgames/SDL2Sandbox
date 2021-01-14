#include "GameOverRenderer.h"
SDL_Renderer* GameOverRenderer::GetMainRenderer() const
{
	return renderer;
}

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
	: renderer(rend)
	, soundManager(sndMan)
	, romFontManager(romFont)
	, gameData(data)
{
}

void GameOverRenderer::DrawMuteHint()
{
	if (soundManager.IsMuted())
	{
		romFontManager.DrawCenteredText(GetMainRenderer(), Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::UNMUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
	else
	{
		romFontManager.DrawCenteredText(GetMainRenderer(), Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::MUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
}

void GameOverRenderer::DrawStartHint()
{
	romFontManager.DrawCenteredText(GetMainRenderer(), Constants::UI::START_MESSAGE_ROW, Constants::UI::START_HINT_TEXT, Constants::Color::MAGENTA);
}

void GameOverRenderer::DrawHints()
{
	if (gameData.GetGameState() == GameState::GAME_OVER)
	{
		DrawMuteHint();
		DrawStartHint();
	}
}
