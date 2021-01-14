#include "GameData.h"
#include "Constants.h"
#include "Utility.h"
GameData::GameData(tggd::common::SoundManager& sndMan)
	: soundManager(sndMan)
	, blockPositions(Constants::Board::ROWS)
	, powerUpPositions(Constants::Board::ROWS)
	, scrollCounter(Constants::Game::InitialValues::COUNTER)
	, direction(Constants::Game::Direction::RIGHT)
	, gameState(GameState::TITLE_SCREEN)
	, runLength(Constants::Game::InitialValues::RUN_LENGTH)
	, score(Constants::Game::InitialValues::SCORE)
	, dead(Constants::Game::InitialValues::DEAD)
	, powerUpCounter(Constants::Game::InitialValues::POWERUP_COUNTER)
	, invincibility(Constants::Game::InitialValues::INVINCIBILITY)
	, keysReversed(Constants::Game::InitialValues::KEYS_REVERSED)
	, bombs(Constants::Game::InitialValues::BOMBS)
	, currentMainMenuItem(MainMenuItem::PLAY)
{

}
static int CalculateScoreFromRunLength(int runLength)
{
	//"triangular number"
	//incentivizes risk by keeping going in a particular direction without turning
	return (runLength * (runLength + 1)) / 2;
}

void GameData::SetNextDirection(int nextDirection)
{
	if (keysReversed)
	{
		nextDirection = -nextDirection;
	}
	if (nextDirection != direction)
	{
		score += CalculateScoreFromRunLength(runLength);
		runLength = Constants::Game::InitialValues::RUN_LENGTH;
		direction = nextDirection;
		soundManager.PlaySound(Constants::Sound::Name::TURN);
	}
}

GameState GameData::GetGameState() const
{
	return gameState;
}

void GameData::UpdateTail()
{
	for (size_t row = 0; row < tailPositions.size() - 1; ++row)
	{
		tailPositions[row] = tailPositions[row + 1];
	}
	tailPositions[tailPositions.size() - 1] = tailPositions[tailPositions.size() - 1] + direction;
}

void GameData::UpdateBlocks()
{
	for (size_t row = 0; row < blockPositions.size() - 1; ++row)
	{
		blockPositions[row] = blockPositions[(size_t)(row + 1)];
	}
	blockPositions[blockPositions.size() - 1] =
		Utility::GenerateRandomFromRange
		(
			Constants::PickUp::MINIMUM_RANDOM_COLUMN,
			Constants::PickUp::MAXIMUM_RANDOM_COLUMN
		);
}

void GameData::UpdateGameStatus()
{
	size_t row = tailPositions.size() - 1;
	if (tailPositions[row] < Constants::Block::MINIMUM_RANDOM_COLUMN ||
		tailPositions[row] > Constants::Block::MAXIMUM_RANDOM_COLUMN)
	{
		gameState = GameState::GAME_OVER;
	}
	else
	{
		if (blockPositions[row] == tailPositions[row])
		{
			switch (GetState())
			{
			case PlayerState::INVINCIBLE:
			case PlayerState::INVINCIBILITY_WEARING_OFF:
				blockPositions[row] = Constants::Block::INITIAL_COLUMN;
				soundManager.PlaySound(Constants::Sound::Name::CHOMP);
				score += Constants::Game::BLOCK_EAT_SCORE;
				break;
			default:
				gameState = GameState::GAME_OVER;
				break;
			}
		}
	}

	if (gameState == GameState::GAME_OVER)
	{
		dead = true;
		soundManager.PlaySound(Constants::Sound::Name::DEATH);
	}
	else
	{
		if (powerUpPositions[row].position == tailPositions[row])
		{
			switch (powerUpPositions[row].type)
			{
			case PowerUpType::BOMB:
				if (bombs < 99)
				{
					bombs++;
				}
				soundManager.PlaySound(Constants::Sound::Name::YOINK);
				break;
			case PowerUpType::DIAMOND:
				score += Constants::PickUp::DIAMOND_BONUS;
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::PENNY:
				score += Constants::PickUp::PENNY_BONUS;
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::DOLLAR:
				score += Constants::PickUp::DOLLAR_BONUS;
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::POUND:
				score += Constants::PickUp::POUND_BONUS;
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::YEN:
				score += Constants::PickUp::YEN_BONUS;
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::REVERSE_KEYS:
				keysReversed = !keysReversed;
				soundManager.PlaySound(Constants::Sound::Name::WHOOPS);
				break;
			case PowerUpType::INVINCIBLE:
				invincibility = Constants::Game::Counters::INVINCIBILITY;
				soundManager.PlaySound(Constants::Sound::Name::CHARGE);
				break;
			}
			powerUpPositions[row].position = Constants::PickUp::INITIAL_COLUMN;
		}
		runLength++;
		if (invincibility > Constants::Game::InitialValues::INVINCIBILITY)
		{
			invincibility--;
		}
	}
}

void GameData::UpdateBoard()
{
	if (gameState==GameState::IN_PLAY)
	{
		UpdateTail();
		UpdateBlocks();
		UpdatePowerUps();
		UpdateGameStatus();
	}
}

void GameData::Update(int milliseconds)
{
	scrollCounter += milliseconds;
	while (scrollCounter > Constants::Game::Counters::SCROLL)
	{
		UpdateBoard();
		scrollCounter -= Constants::Game::Counters::SCROLL;
	}
}

void GameData::UpdatePowerUps()
{
	size_t lastRow = powerUpPositions.size() - 1;
	for (size_t row = 0; row < lastRow; ++row)
	{
		powerUpPositions[row] = powerUpPositions[(size_t)(row + 1)];
	}
	powerUpCounter--;
	if (powerUpCounter <= 0)
	{
		powerUpCounter = GeneratePowerUpCounter();
		powerUpPositions[lastRow].position =
			Utility::GenerateRandomFromRange
			(
				Constants::PickUp::MINIMUM_RANDOM_COLUMN,
				Constants::PickUp::MAXIMUM_RANDOM_COLUMN
			);
		powerUpPositions[lastRow].type = GeneratePowerUp();
	}
	else
	{
		powerUpPositions[lastRow].position = Constants::PickUp::INITIAL_COLUMN;
	}
}

int GameData::GetTailLength() const
{
	return (int)tailPositions.size();
}

int GameData::GetTailPosition(int row) const
{
	return tailPositions[row];
}

int GameData::GetBlockCount() const
{
	return (int)blockPositions.size();
}

int GameData::GetBlockPosition(int row) const
{
	return blockPositions[row];
}

int GameData::GetScore() const
{
	return score;
}

void GameData::ResetGame()
{
	powerUpPositions.clear();
	while (powerUpPositions.size() < Constants::Board::ROWS)
	{
		PowerUp powerUp = { PowerUpType::NONE, Constants::PickUp::INITIAL_COLUMN };
		powerUpPositions.push_back(powerUp);
	}

	blockPositions.clear();
	while (blockPositions.size() < Constants::Board::ROWS)
	{
		blockPositions.push_back(Constants::Block::INITIAL_COLUMN);
	}

	tailPositions.clear();
	while (tailPositions.size() < Constants::Tail::LENGTH)
	{
		tailPositions.push_back(Constants::Tail::INITIAL_COLUMN);
	}

	direction = Constants::Game::Direction::RIGHT;
	score = Constants::Game::InitialValues::SCORE;
	runLength = Constants::Game::InitialValues::RUN_LENGTH;
	dead = Constants::Game::InitialValues::DEAD;
	invincibility = Constants::Game::InitialValues::INVINCIBILITY;
	bombs = Constants::Game::InitialValues::BOMBS;
	keysReversed = Constants::Game::InitialValues::KEYS_REVERSED;
}

void GameData::RestartGame()
{
	ResetGame();
	gameState = GameState::IN_PLAY;
}

int GameData::GetPowerUpCount() const
{
	return (int)powerUpPositions.size();
}

int GameData::GetPowerUpPosition(int row) const
{
	return powerUpPositions[row].position;
}

int GameData::GeneratePowerUpCounter()
{
	return Utility::GenerateRandomFromRange(1, 6) + Utility::GenerateRandomFromRange(1, 6);
}

std::map<PowerUpType, int> GameData::powerUpGenerator;
PowerUpType GameData::GeneratePowerUp()
{
	if (powerUpGenerator.empty())
	{
		powerUpGenerator[PowerUpType::PENNY] = 1;
		powerUpGenerator[PowerUpType::DOLLAR] = 1;
		powerUpGenerator[PowerUpType::POUND] = 1;
		powerUpGenerator[PowerUpType::YEN] = 1;
		powerUpGenerator[PowerUpType::DIAMOND] = 1;
		powerUpGenerator[PowerUpType::INVINCIBLE] = 1;
		powerUpGenerator[PowerUpType::REVERSE_KEYS] = 1;
		powerUpGenerator[PowerUpType::BOMB] = 1;
	}
	int tally = 0;
	for (const auto& entry : powerUpGenerator)
	{
		tally += entry.second;
	}
	int generated = Utility::GenerateRandomFromRange(0, tally - 1);
	for (const auto& entry : powerUpGenerator)
	{
		if (generated < entry.second)
		{
			return entry.first;
		}
		else
		{
			generated -= entry.second;
		}
	}
	return PowerUpType::NONE;
}

PowerUpType GameData::GetPowerUp(int row) const
{
	return powerUpPositions[row].type;
}

PlayerState GameData::GetState() const
{
	if (dead)
	{
		return PlayerState::DEAD;
	}
	else if (invincibility > Constants::Game::Counters::INVINCIBILITY_WEAR_OFF)
	{
		return PlayerState::INVINCIBLE;
	}
	else if (invincibility > 0)
	{
		return PlayerState::INVINCIBILITY_WEARING_OFF;
	}
	else
	{
		return PlayerState::NORMAL;
	}
}

void GameData::UseBomb()
{
	if (gameState==GameState::IN_PLAY && bombs > 0)
	{
		bombs--;
		for (auto& block : blockPositions)
		{
			block = Constants::Block::INITIAL_COLUMN;
		}
		soundManager.PlaySound(Constants::Sound::Name::BOOM);
	}
}

int GameData::GetBombs() const
{
	return bombs;
}

MainMenuItem GameData::GetMainMenuItem() const
{
	return currentMainMenuItem;
}

void GameData::NextMainMenuItem()
{
	switch (currentMainMenuItem)
	{
	case MainMenuItem::PLAY:
		currentMainMenuItem = MainMenuItem::INSTRUCTIONS;
		break;
	case MainMenuItem::INSTRUCTIONS:
		currentMainMenuItem = MainMenuItem::ABOUT;
		break;
	case MainMenuItem::ABOUT:
		currentMainMenuItem = MainMenuItem::OPTIONS;
		break;
	case MainMenuItem::OPTIONS:
		currentMainMenuItem = MainMenuItem::QUIT;
		break;
	case MainMenuItem::QUIT:
		currentMainMenuItem = MainMenuItem::PLAY;
		break;
	}
}

void GameData::PreviousMainMenuItem()
{
	switch (currentMainMenuItem)
	{
	case MainMenuItem::PLAY:
		currentMainMenuItem = MainMenuItem::QUIT;
		break;
	case MainMenuItem::INSTRUCTIONS:
		currentMainMenuItem = MainMenuItem::PLAY;
		break;
	case MainMenuItem::ABOUT:
		currentMainMenuItem = MainMenuItem::INSTRUCTIONS;
		break;
	case MainMenuItem::OPTIONS:
		currentMainMenuItem = MainMenuItem::ABOUT;
		break;
	case MainMenuItem::QUIT:
		currentMainMenuItem = MainMenuItem::OPTIONS;
		break;
	}
}
