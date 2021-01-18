#include "GameData.h"
#include "..\Constants\Board.h"
#include "..\Constants\Game.h"
#include "..\Constants\Sound.h"
#include "..\Utility.h"
#include "..\Constants\PowerUp.h"
#include "..\Constants\Block.h"
#include "..\Constants\Tail.h"
GameData::GameData(tggd::common::SoundManager& sndMan, GameState& gameState)
	: soundManager(sndMan)
	, blockPositions(Constants::Board::ROWS)
	, powerUpPositions(Constants::Board::ROWS)
	, scrollCounter(Constants::Game::InitialValues::COUNTER)
	, direction(Constants::Game::Direction::RIGHT)
	, gameState(gameState)
	, runLength(Constants::Game::InitialValues::RUN_LENGTH)
	, score(Constants::Game::InitialValues::SCORE)
	, dead(Constants::Game::InitialValues::DEAD)
	, powerUpCounter(Constants::Game::InitialValues::POWERUP_COUNTER)
	, invincibility(Constants::Game::InitialValues::INVINCIBILITY)
	, keysReversed(Constants::Game::InitialValues::KEYS_REVERSED)
	, bombs(Constants::Game::InitialValues::BOMBS)
	, lives(Constants::Game::InitialValues::LIVES)
	, scoreMultiplier(Constants::Game::InitialValues::SCORE_MULTIPLIER)
	, scoreDivisor(Constants::Game::InitialValues::SCORE_DIVISOR)
	, scrollCounterMaximum(Constants::Game::Counters::SCROLL)
	, shield(Constants::Game::InitialValues::SHIELD)
{

}
static int CalculateScoreFromRunLength(int runLength)
{
	//"triangular number"
	//incentivizes risk by keeping going in a particular direction without turning
	return (runLength * (runLength + 1)) / 2;
}

void GameData::AddScore(int amount)
{
	score += amount * scoreMultiplier / scoreDivisor;
}

void GameData::SetNextDirection(int nextDirection)
{
	if (keysReversed)
	{
		nextDirection = -nextDirection;
	}
	if (nextDirection != direction)
	{
		AddScore(CalculateScoreFromRunLength(runLength));
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
			Constants::PowerUp::MINIMUM_RANDOM_COLUMN,
			Constants::PowerUp::MAXIMUM_RANDOM_COLUMN
		);
}

void GameData::UpdateGameStatus()
{
	size_t row = tailPositions.size() - 1;
	if (tailPositions[row] < Constants::Block::MINIMUM_RANDOM_COLUMN ||
		tailPositions[row] > Constants::Block::MAXIMUM_RANDOM_COLUMN)
	{
		LoseLife();
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
				AddScore(Constants::Game::BLOCK_EAT_SCORE);
				break;
			case PlayerState::SHIELDED:
				shield--;
				blockPositions[row] = Constants::Block::INITIAL_COLUMN;
				//TODO: play sound
				break;
			default:
				LoseLife();
				break;
			}
		}
	}

	if (gameState == GameState::GAME_OVER || gameState == GameState::END_RUN)
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
			case PowerUpType::SHIELD:
				if (shield < Constants::Game::Maximums::SHIELD)
				{
					shield++;
					//TODO: shield
				}
				else
				{
					soundManager.PlaySound(Constants::Sound::Name::NOPE);
				}
				break;
			case PowerUpType::INSTANT_BOMB:
				bombs++;
				UseBomb();
				break;
			case PowerUpType::SPEED_NORMAL:
				//TODO: sound
				scrollCounterMaximum = Constants::Game::Counters::SCROLL;
				break;
			case PowerUpType::SPEED_UP:
				//TODO: sound
				scrollCounterMaximum = Constants::Game::Counters::FAST_SCROLL;
				break;
			case PowerUpType::SLOW_DOWN:
				//TODO: sound
				scrollCounterMaximum = Constants::Game::Counters::SLOW_SCROLL;
				break;
			case PowerUpType::SCORE_DOUBLE:
				scoreMultiplier = 2;
				scoreDivisor = 1;
				//TODO: sound
				break;
			case PowerUpType::SCORE_HALF:
				scoreMultiplier = 1;
				scoreDivisor = 2;
				//TODO: sound
				break;
			case PowerUpType::SCORE_NORMAL:
				scoreMultiplier = 1;
				scoreDivisor = 1;
				//TODO: sound
				break;
			case PowerUpType::SCORE_QUADRUPAL:
				scoreMultiplier = 4;
				scoreDivisor = 1;
				//TODO: sound
				break;
			case PowerUpType::SCORE_QUARTER:
				scoreMultiplier = 1;
				scoreDivisor = 4;
				//TODO: sound
				break;
			case PowerUpType::BOMB:
				if (bombs < Constants::Game::Maximums::BOMBS)
				{
					bombs++;
					soundManager.PlaySound(Constants::Sound::Name::YOINK);
				}
				else
				{
					soundManager.PlaySound(Constants::Sound::Name::NOPE);
				}
				break;
			case PowerUpType::DIAMOND:
				AddScore(Constants::PowerUp::DIAMOND_BONUS);
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::PENNY:
				AddScore(Constants::PowerUp::PENNY_BONUS);
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::DOLLAR:
				AddScore(Constants::PowerUp::DOLLAR_BONUS);
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::POUND:
				AddScore(Constants::PowerUp::POUND_BONUS);
				soundManager.PlaySound(Constants::Sound::Name::TING);
				break;
			case PowerUpType::YEN:
				AddScore(Constants::PowerUp::YEN_BONUS);
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
			case PowerUpType::EXTRA_LIFE:
				if (lives < Constants::Game::Maximums::LIVES)
				{
					lives++;
					soundManager.PlaySound(Constants::Sound::Name::WOOHOO);
				}
				else
				{
					soundManager.PlaySound(Constants::Sound::Name::NOPE);
				}
				break;
			}
			powerUpPositions[row].position = Constants::PowerUp::INITIAL_COLUMN;
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
	while (scrollCounter > scrollCounterMaximum)
	{
		UpdateBoard();
		scrollCounter -= scrollCounterMaximum;
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
				Constants::PowerUp::MINIMUM_RANDOM_COLUMN,
				Constants::PowerUp::MAXIMUM_RANDOM_COLUMN
			);
		powerUpPositions[lastRow].type = GeneratePowerUp();
	}
	else
	{
		powerUpPositions[lastRow].position = Constants::PowerUp::INITIAL_COLUMN;
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

void GameData::ResetRun()
{
	powerUpPositions.clear();
	while (powerUpPositions.size() < Constants::Board::ROWS)
	{
		PowerUp powerUp = { PowerUpType::NONE, Constants::PowerUp::INITIAL_COLUMN };
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
	runLength = Constants::Game::InitialValues::RUN_LENGTH;
	dead = Constants::Game::InitialValues::DEAD;
	invincibility = Constants::Game::InitialValues::INVINCIBILITY;
	bombs = Constants::Game::InitialValues::BOMBS;
	scoreMultiplier = Constants::Game::InitialValues::SCORE_MULTIPLIER;
	scoreDivisor = Constants::Game::InitialValues::SCORE_DIVISOR;
	keysReversed = Constants::Game::InitialValues::KEYS_REVERSED;
	scrollCounterMaximum = Constants::Game::Counters::SCROLL;
	shield = Constants::Game::InitialValues::SHIELD;
}

void GameData::ResetGame()
{
	ResetRun();

	score = Constants::Game::InitialValues::SCORE;
	lives = Constants::Game::InitialValues::LIVES;
}

void GameData::NextRun()
{
	ResetRun();
	gameState = GameState::IN_PLAY;
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
		powerUpGenerator[PowerUpType::DIAMOND] = 1;
		powerUpGenerator[PowerUpType::POUND] = 1;
		powerUpGenerator[PowerUpType::YEN] = 1;

		powerUpGenerator[PowerUpType::SCORE_NORMAL] = 1;
		powerUpGenerator[PowerUpType::SCORE_DOUBLE] = 1;
		powerUpGenerator[PowerUpType::SCORE_QUADRUPAL] = 1;
		powerUpGenerator[PowerUpType::SCORE_HALF] = 1;
		powerUpGenerator[PowerUpType::SCORE_QUARTER] = 1;

		powerUpGenerator[PowerUpType::INVINCIBLE] = 1;
		powerUpGenerator[PowerUpType::REVERSE_KEYS] = 1;
		powerUpGenerator[PowerUpType::BOMB] = 1;
		powerUpGenerator[PowerUpType::EXTRA_LIFE] = 1;

		powerUpGenerator[PowerUpType::SPEED_UP] = 1;
		powerUpGenerator[PowerUpType::SLOW_DOWN] = 1;
		powerUpGenerator[PowerUpType::SPEED_NORMAL] = 1;
		powerUpGenerator[PowerUpType::INSTANT_BOMB] = 1;
		powerUpGenerator[PowerUpType::SHIELD] = 1;
		powerUpGenerator[PowerUpType::CHANGE_DIRECTION] = 1;

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
	else if (shield > 0)
	{
		return PlayerState::SHIELDED;
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
	else
	{
		soundManager.PlaySound(Constants::Sound::Name::NOPE);
	}
}

int GameData::GetBombs() const
{
	return bombs;
}


void GameData::SetGameState(const GameState& state)
{
	gameState = state;
}

void GameData::LoseLife()
{
	if (lives > 0)
	{
		lives--;
		if (lives > 0)
		{
			SetGameState(GameState::END_RUN);
		}
		else
		{
			SetGameState(GameState::GAME_OVER);
		}
	}
}

int GameData::GetLives() const
{
	return lives;
}

int GameData::GetScoreMultiplier() const
{
	return scoreMultiplier;
}

int GameData::GetScoreDivisor() const
{
	return scoreDivisor;
}

int GameData::GetShield() const
{
	return shield;
}
