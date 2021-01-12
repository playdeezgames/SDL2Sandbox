#include "JetLag2021Renderer.h"
#include <SDL_image.h>
#include <sstream>
JetLag2021Renderer::JetLag2021Renderer
	(
		const GameData& data, 
		const tggd::common::SoundManager& sndMan
	)
	: renderer(nullptr)
	, gameData(data)
	, soundManager(sndMan)
	, romfontTexture(nullptr)
	, romfontSrcRects()
{
}

void JetLag2021Renderer::Start(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	for (int index = 0; index < Constants::RomFont::CELL_COUNT; ++index)
	{
		int column = index % Constants::RomFont::COLUMNS;
		int row = index / Constants::RomFont::COLUMNS;
		romfontSrcRects[index].x = column * Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].y = row * Constants::RomFont::CELL_HEIGHT;
		romfontSrcRects[index].w = Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].h = Constants::RomFont::CELL_HEIGHT;
	}
	romfontTexture = IMG_LoadTexture(renderer, Constants::RomFont::IMAGE_FILE_NAME.c_str());
}

void JetLag2021Renderer::Finish()
{
	SDL_DestroyTexture(romfontTexture);
	renderer = nullptr;
}

void JetLag2021Renderer::Draw()
{
	DrawBackground();
	DrawBlocks();
	DrawPickUps();
	DrawWalls();
	DrawTail();
	DrawStatusBar();
	DrawScore();
	DrawBombs();
	DrawHints();
}

void JetLag2021Renderer::DrawBackground()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void JetLag2021Renderer::DrawTail()
{
	for (int row = 0; row < gameData.GetTailLength() - 1; ++row)
	{
		DrawCharacter(gameData.GetTailPosition(row), row, '*', Constants::Color::BROWN);
	}
	switch (gameData.GetState())
	{
	case PlayerState::DEAD:
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x0F', Constants::Color::RED);
		break;
	case PlayerState::INVINCIBILITY_WEARING_OFF:
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::LIGHT_RED);
		break;
	case PlayerState::INVINCIBLE:
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::CYAN);
		break;
	case PlayerState::NORMAL:
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::WHITE);
		break;

	}
}

void JetLag2021Renderer::PlotCellRect(SDL_Rect& rc, int column, int row)
{
	rc.x = column * Constants::Cell::WIDTH;
	rc.y = row * Constants::Cell::HEIGHT;
	rc.w = Constants::Cell::WIDTH;
	rc.h = Constants::Cell::HEIGHT;
}

void JetLag2021Renderer::DrawBlocks()
{
	for (int row = 0; row < gameData.GetBlockCount(); ++row)
	{
		DrawCharacter(gameData.GetBlockPosition(row), row, (char)0xdb, Constants::Color::WHITE);
	}
}

void JetLag2021Renderer::DrawWalls()
{
	for (int row = 0; row < Constants::Board::ROWS; ++row)
	{
		DrawCharacter(Constants::Board::LEFT_WALL, row, (char)0xdb, Constants::Color::BLUE);
		DrawCharacter(Constants::Board::RIGHT_WALL, row, (char)0xdb, Constants::Color::BLUE);
	}
}

void JetLag2021Renderer::DrawBombs()
{
	std::stringstream ss;
	ss << '\x0f' << (char)('0' + (gameData.GetBombs() / Constants::Game::SCORE_RADIX)) << (char)('0' + (gameData.GetBombs() % Constants::Game::SCORE_RADIX));
	DrawText(Constants::Board::COLUMNS - 3, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawScore()
{
	std::stringstream ss;
	ss << gameData.GetScore();
	DrawText(0, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawMuteHint()
{
	if (soundManager.IsMuted())
	{
		DrawCenteredText(Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::UNMUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
	else
	{
		DrawCenteredText(Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::MUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
}

void JetLag2021Renderer::DrawStartHint()
{
	DrawCenteredText(Constants::UI::START_MESSAGE_ROW, Constants::UI::START_HINT_TEXT, Constants::Color::MAGENTA);
}

void JetLag2021Renderer::DrawHints()
{
	if (gameData.IsGameOver())
	{
		DrawMuteHint();
		DrawStartHint();
	}
}

void JetLag2021Renderer::DrawCenteredText(int row, const std::string& text, const SDL_Color& color)
{
	//you center things by dividing by 2
	DrawText((Constants::Board::COLUMNS - (int)text.size()) / 2, row, text, color);
}

void JetLag2021Renderer::DrawCharacter(int column, int row, char character, const SDL_Color& color)
{
	SDL_SetTextureColorMod(romfontTexture, color.r, color.g, color.b);
	SDL_Rect rcDst =
	{
		column * Constants::Cell::WIDTH,
		row * Constants::Cell::HEIGHT,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	SDL_RenderCopy(renderer, romfontTexture, &(romfontSrcRects[(unsigned char)character]), &rcDst);
}

void JetLag2021Renderer::DrawText(int column, int row, const std::string& text, const SDL_Color& color)
{
	for (auto ch : text)
	{
		DrawCharacter(column, row, ch, color);
		column++;
	}
}

void JetLag2021Renderer::DrawPickUps()
{
	for (int row = 0; row < gameData.GetPowerUpCount(); ++row)
	{
		char ch = 0;
		SDL_Color color = Constants::Color::BLACK;
		switch (gameData.GetPowerUp(row))
		{
		case PowerUpType::REVERSE_KEYS:
			color = Constants::Color::DARK_GRAY;
			ch = '?';
			break;
		case PowerUpType::BOMB:
			color = Constants::Color::DARK_GRAY;
			ch = 15;
			break;
		case PowerUpType::DIAMOND:
			color = Constants::Color::YELLOW;
			ch = 0x04;
			break;
		case PowerUpType::PENNY:
			color = Constants::Color::YELLOW;
			ch = (char)0x9b;
			break;
		case PowerUpType::DOLLAR:
			color = Constants::Color::YELLOW;
			ch = 0x24;
			break;
		case PowerUpType::POUND:
			color = Constants::Color::YELLOW;
			ch = (char)0x9c;
			break;
		case PowerUpType::YEN:
			color = Constants::Color::YELLOW;
			ch = (char)0x9d;
			break;
		case PowerUpType::INVINCIBLE:
			color = Constants::Color::RED;
			ch = 0x03;
		}
		DrawCharacter(gameData.GetPowerUpPosition(row), row, ch, color);
	}
}

void JetLag2021Renderer::DrawStatusBar()
{
	for (int column = 0; column < Constants::Board::COLUMNS; ++column)
	{
		DrawCharacter(column, 0, (char)0xdb, Constants::Color::BROWN);
	}
}