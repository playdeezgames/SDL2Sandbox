#include "GameData.h"
#include "Constants.h"
#include "Utility.h"
GameData::GameData()
	: blocks(Constants::Board::ROWS)
	, pickUps(Constants::Board::ROWS)
	, counter(Constants::Game::InitialValues::COUNTER)
	, direction(Constants::Game::Direction::RIGHT)
	, gameOver(Constants::Game::InitialValues::GAME_OVER)
	, runLength(Constants::Game::InitialValues::RUN_LENGTH)
	, score(Constants::Game::InitialValues::SCORE)
	, dead(Constants::Game::InitialValues::DEAD)
{

}
static int CalculateScoreFromRunLength(int runLength)
{
	//"triangular number"
	//incentivizes risk by keeping going in a particular direction without turning
	return (runLength * (runLength + 1)) / 2;
}

bool GameData::SetNextDirection(int nextDirection)
{
	if (nextDirection != direction)
	{
		score += CalculateScoreFromRunLength(runLength);
		runLength = Constants::Game::InitialValues::RUN_LENGTH;
		direction = nextDirection;
		return true;
	}
	return false;
}

bool GameData::IsGameOver() const
{
	return gameOver;
}

void GameData::UpdateTail()
{
	for (size_t row = 0; row < tail.size() - 1; ++row)
	{
		tail[row] = tail[row + 1];
	}
	tail[tail.size() - 1] = tail[tail.size() - 1] + direction;
}

void GameData::UpdateBlocks()
{
	for (size_t row = 0; row < blocks.size() - 1; ++row)
	{
		blocks[row] = blocks[(size_t)(row + 1)];
	}
	blocks[blocks.size() - 1] =
		Utility::GenerateRandomFromRange
		(
			Constants::PickUp::MINIMUM_RANDOM_COLUMN,
			Constants::PickUp::MAXIMUM_RANDOM_COLUMN
		);
}

void GameData::UpdateGameStatus()
{
	gameOver =
		blocks[tail.size() - 1] == tail[tail.size() - 1] ||
		tail[tail.size() - 1] < Constants::Block::MINIMUM_RANDOM_COLUMN ||
		tail[tail.size() - 1] > Constants::Block::MAXIMUM_RANDOM_COLUMN;

	if (gameOver)
	{
		dead = true;
		//TODO: soundManager.Play(Constants::Sound::DEATH);
	}
	else
	{
		if (pickUps[tail.size() - 1] == tail[tail.size() - 1])
		{
			pickUps[tail.size() - 1] = Constants::PickUp::INITIAL_COLUMN;
			score += Constants::PickUp::SCORE_BONUS;
			//TODO: soundManager.Play(Constants::Sound::CHOMP);
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
		UpdatePickUps();
		UpdateGameStatus();
	}
}

void GameData::Update(int milliseconds)
{
	counter += milliseconds;
	while (counter > Constants::Game::FRAME_MILLISECONDS)
	{
		UpdateBoard();
		counter -= Constants::Game::FRAME_MILLISECONDS;
	}
}

void GameData::UpdatePickUps()
{
	for (size_t row = 0; row < pickUps.size() - 1; ++row)
	{
		pickUps[row] = pickUps[(size_t)(row + 1)];
	}
	pickUps[pickUps.size() - 1] =
		Utility::GenerateRandomFromRange
		(
			Constants::PickUp::MINIMUM_RANDOM_COLUMN,
			Constants::PickUp::MAXIMUM_RANDOM_COLUMN
		);
}

int GameData::GetTailLength() const
{
	return (int)tail.size();
}

int GameData::GetTailPosition(int row) const
{
	return tail[row];
}

bool GameData::IsDead() const
{
	return dead;
}

int GameData::GetBlockCount() const
{
	return (int)blocks.size();
}

int GameData::GetBlockPosition(int row) const
{
	return blocks[row];
}

int GameData::GetScore() const
{
	return score;
}

void GameData::ResetGame()
{
	pickUps.clear();
	while (pickUps.size() < Constants::Board::ROWS)
	{
		pickUps.push_back(Constants::PickUp::INITIAL_COLUMN);
	}

	blocks.clear();
	while (blocks.size() < Constants::Board::ROWS)
	{
		blocks.push_back(Constants::Block::INITIAL_COLUMN);
	}

	tail.clear();
	while (tail.size() < Constants::Tail::LENGTH)
	{
		tail.push_back(Constants::Tail::INITIAL_COLUMN);
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

int GameData::GetPickUpCount() const
{
	return (int)pickUps.size();
}

int GameData::GetPickUpPosition(int row) const
{
	return pickUps[row];
}
