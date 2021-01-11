#include "GameData.h"
#include "Constants.h"
#include "Utility.h"
GameData::GameData(tggd::common::SoundManager& sndMan)
	: soundManager(sndMan)
	, blockPositions(Constants::Board::ROWS)
	, powerUpPositions(Constants::Board::ROWS)
	, scrollCounter(Constants::Game::InitialValues::COUNTER)
	, direction(Constants::Game::Direction::RIGHT)
	, gameOver(Constants::Game::InitialValues::GAME_OVER)
	, runLength(Constants::Game::InitialValues::RUN_LENGTH)
	, score(Constants::Game::InitialValues::SCORE)
	, dead(Constants::Game::InitialValues::DEAD)
	, powerUpCounter(0)
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
	if (nextDirection != direction)
	{
		score += CalculateScoreFromRunLength(runLength);
		runLength = Constants::Game::InitialValues::RUN_LENGTH;
		direction = nextDirection;
		soundManager.Play(Constants::Sound::TURN);
	}
}

bool GameData::IsGameOver() const
{
	return gameOver;
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
	gameOver =
		blockPositions[row] == tailPositions[row] ||
		tailPositions[row] < Constants::Block::MINIMUM_RANDOM_COLUMN ||
		tailPositions[row] > Constants::Block::MAXIMUM_RANDOM_COLUMN;

	if (gameOver)
	{
		dead = true;
		soundManager.Play(Constants::Sound::DEATH);
	}
	else
	{
		if (powerUpPositions[row].position == tailPositions[row])
		{
			switch (powerUpPositions[row].type)
			{
			case PowerUpType::DIAMOND:
				score += Constants::PickUp::SCORE_BONUS;
				soundManager.Play(Constants::Sound::CHOMP);
				break;
			}
			powerUpPositions[row].position = Constants::PickUp::INITIAL_COLUMN;
		}
		runLength++;
	}
}

void GameData::UpdateBoard()
{
	if (!gameOver)
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
	while (scrollCounter > Constants::Game::FRAME_MILLISECONDS)
	{
		UpdateBoard();
		scrollCounter -= Constants::Game::FRAME_MILLISECONDS;
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

bool GameData::IsDead() const
{
	return dead;
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
}

void GameData::RestartGame()
{
	ResetGame();
	gameOver = false;
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
		powerUpGenerator[PowerUpType::DIAMOND] = 1;
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
