#include "JetLag2021Renderer.h"
#include <SDL_image.h>
#include <sstream>
#include "..\Constants\Color.h"
#include "..\Constants\Board.h"
#include "..\Constants\Game.h"
JetLag2021Renderer::JetLag2021Renderer
	(
		const GameData& data, 
		const tggd::common::SoundManager& sndMan, 
		const RomFontManager& romFont
	)
	: renderer(nullptr)
	, gameData(data)
	, soundManager(sndMan)
	, romFontManager(romFont)
{
}

void JetLag2021Renderer::Start(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void JetLag2021Renderer::Finish()
{
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
	DrawLives();
	DrawScoreMultiplier();
	DrawShield();
}

void JetLag2021Renderer::DrawShield()
{
	std::stringstream ss;
	ss << '\xe9' << (char)('0' + (gameData.GetShield() / Constants::Game::SCORE_RADIX)) << (char)('0' + (gameData.GetShield() % Constants::Game::SCORE_RADIX));
	romFontManager.DrawText(GetMainRenderer(), Constants::Board::COLUMNS - 14, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawScoreMultiplier()
{
	char ch = '1';
	switch (gameData.GetScoreDivisor())
	{
	case 4:
		ch = '\xac';
		break;
	case 2:
		ch = '\xab';
		break;
	default:
		ch = '0' + gameData.GetScoreMultiplier();
	}
	romFontManager.DrawCharacter(GetMainRenderer(), Constants::Board::COLUMNS - 10, 0, 'x', Constants::Color::BLACK);
	romFontManager.DrawCharacter(GetMainRenderer(),Constants::Board::COLUMNS - 9, 0, ch, Constants::Color::BLACK);
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
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(row), row, '*', Constants::Color::BROWN);
	}
	switch (gameData.GetState())
	{
	case PlayerState::DEAD:
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x0F', Constants::Color::RED);
		break;
	case PlayerState::INVINCIBILITY_WEARING_OFF:
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::LIGHT_RED);
		break;
	case PlayerState::INVINCIBLE:
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::CYAN);
		break;
	case PlayerState::SHIELDED:
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x01', Constants::Color::LIGHT_BLUE);
		break;
	case PlayerState::NORMAL:
		romFontManager.DrawCharacter(renderer, gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::WHITE);
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
		romFontManager.DrawCharacter(renderer, gameData.GetBlockPosition(row), row, (char)0xdb, Constants::Color::WHITE);
	}
}

void JetLag2021Renderer::DrawWalls()
{
	for (int row = 0; row < Constants::Board::ROWS; ++row)
	{
		romFontManager.DrawCharacter(renderer, Constants::Board::LEFT_WALL, row, (char)0xdb, Constants::Color::BLUE);
		romFontManager.DrawCharacter(renderer, Constants::Board::RIGHT_WALL, row, (char)0xdb, Constants::Color::BLUE);
	}
}

void JetLag2021Renderer::DrawBombs()
{
	std::stringstream ss;
	ss << '\x0f' << (char)('0' + (gameData.GetBombs() / Constants::Game::SCORE_RADIX)) << (char)('0' + (gameData.GetBombs() % Constants::Game::SCORE_RADIX));
	romFontManager.DrawText(GetMainRenderer(), Constants::Board::COLUMNS - 3, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawLives()
{
	std::stringstream ss;
	ss << '\x01' << (char)('0' + (gameData.GetLives() / Constants::Game::SCORE_RADIX)) << (char)('0' + (gameData.GetLives() % Constants::Game::SCORE_RADIX));
	romFontManager.DrawText(GetMainRenderer(), Constants::Board::COLUMNS - 7, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawScore()
{
	std::stringstream ss;
	ss << gameData.GetScore();
	romFontManager.DrawText(GetMainRenderer(), 0, 0, ss.str(), Constants::Color::BLACK);
}

void JetLag2021Renderer::DrawPickUps()
{
	for (int row = 0; row < gameData.GetPowerUpCount(); ++row)
	{
		char ch = 0;
		SDL_Color color = Constants::Color::BLACK;
		switch (gameData.GetPowerUp(row))
		{
		case PowerUpType::SHIELD:
			color = Constants::Color::LIGHT_BLUE;
			ch = '\xe9';
			break;
		case PowerUpType::INSTANT_BOMB:
			color = Constants::Color::RED;
			ch = '!';
			break;
		case PowerUpType::SPEED_UP:
			color = Constants::Color::MAGENTA;
			ch = '\x18';
			break;
		case PowerUpType::SLOW_DOWN:
			color = Constants::Color::MAGENTA;
			ch = '\x19';
			break;
		case PowerUpType::SPEED_NORMAL:
			color = Constants::Color::MAGENTA;
			ch = '\x12';
			break;
		case PowerUpType::SCORE_DOUBLE:
			color = Constants::Color::GREEN;
			ch = '2';
			break;
		case PowerUpType::SCORE_HALF:
			color = Constants::Color::GREEN;
			ch = '\xab';
			break;
		case PowerUpType::SCORE_NORMAL:
			color = Constants::Color::GREEN;
			ch = '1';
			break;
		case PowerUpType::SCORE_QUADRUPAL:
			color = Constants::Color::GREEN;
			ch = '4';
			break;
		case PowerUpType::SCORE_QUARTER:
			color = Constants::Color::GREEN;
			ch = '\xac';
			break;
		case PowerUpType::EXTRA_LIFE:
			color = Constants::Color::WHITE;
			ch = '\x01';
			break;
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
		romFontManager.DrawCharacter(renderer, gameData.GetPowerUpPosition(row), row, ch, color);
	}
}

void JetLag2021Renderer::DrawStatusBar()
{
	for (int column = 0; column < Constants::Board::COLUMNS; ++column)
	{
		romFontManager.DrawCharacter(renderer, column, 0, (char)0xdb, Constants::Color::BROWN);
	}
}

SDL_Renderer* JetLag2021Renderer::GetMainRenderer() const
{
	return renderer;
}
