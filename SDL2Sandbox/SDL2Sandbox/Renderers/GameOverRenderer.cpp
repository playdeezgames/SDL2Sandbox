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

void GameOverRenderer::DrawMenuHint()
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::UI::MENU_MESSAGE_ROW, Constants::UI::MENU_HINT_TEXT, Constants::Color::MAGENTA);
}

void GameOverRenderer::DrawStartHint()
{
	GetRomFont().DrawCenteredText(GetMainRenderer(), Constants::UI::RESTART_MESSAGE_ROW, Constants::UI::RESTART_HINT_TEXT, Constants::Color::MAGENTA);
}

void GameOverRenderer::DrawHints()
{
	DrawMenuHint();
	DrawStartHint();
}
