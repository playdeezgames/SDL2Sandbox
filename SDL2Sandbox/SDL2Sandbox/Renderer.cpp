#include "Renderer.h"
#include <SDL_image.h>
Renderer::Renderer
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

void Renderer::Start(SDL_Renderer* renderer)
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

void Renderer::Finish()
{
	SDL_DestroyTexture(romfontTexture);
	renderer = nullptr;
}

void Renderer::Draw() 
{
	DrawBackground();
	DrawBlocks();
	DrawPickUps();
	DrawWalls();
	DrawTail();
	DrawScore();
	DrawHints();
}

void Renderer::DrawBackground()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::DrawTail()
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

void Renderer::PlotCellRect(SDL_Rect& rc, int column, int row)
{
	rc.x = column * Constants::Cell::WIDTH;
	rc.y = row * Constants::Cell::HEIGHT;
	rc.w = Constants::Cell::WIDTH;
	rc.h = Constants::Cell::HEIGHT;
}

void Renderer::DrawBlocks()
{
	for (int row = 0; row < gameData.GetBlockCount(); ++row)
	{
		DrawCharacter(gameData.GetBlockPosition(row), row, (char)0xdb, Constants::Color::WHITE);
	}
}

void Renderer::DrawWalls()
{
	for (int row = 0; row < Constants::Board::ROWS; ++row)
	{
		DrawCharacter(Constants::Board::LEFT_WALL, row, (char)0xdb, Constants::Color::BLUE);
		DrawCharacter(Constants::Board::RIGHT_WALL, row, (char)0xdb, Constants::Color::BLUE);
	}
}

void Renderer::DrawScore()
{
	SDL_SetTextureColorMod(romfontTexture, 0, 255, 0);
	SDL_Rect rc =
	{
		Constants::Cell::WIDTH,
		Constants::Utility::DEFAULT_Y,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	int digits = 1;//there is always at least one score digit
	int temp = gameData.GetScore();
	while (temp >= Constants::Game::SCORE_RADIX)
	{
		digits++;
		temp /= Constants::Game::SCORE_RADIX;
		rc.x += Constants::Cell::WIDTH;
	}
	temp = gameData.GetScore();
	while (digits)
	{
		int digit = temp % Constants::Game::SCORE_RADIX;
		temp /= Constants::Game::SCORE_RADIX;
		digits--;
		SDL_RenderCopy(renderer, romfontTexture, &(romfontSrcRects['0' + digit]), &rc);
		rc.x -= Constants::Cell::WIDTH;
	}
}

void Renderer::DrawMuteHint()
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

void Renderer::DrawStartHint()
{
	DrawCenteredText(Constants::UI::START_MESSAGE_ROW, Constants::UI::START_HINT_TEXT, Constants::Color::MAGENTA);
}

void Renderer::DrawHints()
{
	if (gameData.IsGameOver())
	{
		DrawMuteHint();
		DrawStartHint();
	}
}

void Renderer::DrawCenteredText(int row, const std::string& text, const SDL_Color& color)
{
	//you center things by dividing by 2
	DrawText((Constants::Board::COLUMNS - (int)text.size()) / 2, row, text, color);
}

void Renderer::DrawCharacter(int column, int row, char character, const SDL_Color& color)
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

void Renderer::DrawText(int column, int row, const std::string& text, const SDL_Color& color)
{
	for (auto ch : text)
	{
		DrawCharacter(column, row, ch, color);
		column++;
	}
}

void Renderer::DrawPickUps()
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

