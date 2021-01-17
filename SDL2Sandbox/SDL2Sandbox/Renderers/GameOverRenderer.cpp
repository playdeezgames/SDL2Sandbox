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
		const RomFontManager& romFont
	)
	: BaseRenderer(rend, romFont)
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
