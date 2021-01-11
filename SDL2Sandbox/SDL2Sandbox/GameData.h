#pragma once
#include <vector>
#include "..\..\..\CommonCpp\SoundManager.h"
enum PowerUpType
{
	POWERUP_NONE,
	POWERUP_DIAMOND
};
struct PowerUp
{
	int type;
	int position;
};
class GameData
{
private:
	const tggd::common::SoundManager& soundManager;
	std::vector<int> blockPositions;
	std::vector<PowerUp> powerUpPositions;
	int powerUpCounter;
	std::vector<int> tailPositions;
	int scrollCounter;
	int direction;
	bool gameOver;
	int score;
	int runLength;
	bool dead;

	static int GeneratePowerUpCounter();
public:
	GameData(tggd::common::SoundManager&);

	int GetTailLength() const;
	int GetTailPosition(int) const;
	void SetNextDirection(int);

	int GetBlockCount() const;
	int GetBlockPosition(int) const;

	int GetPowerUpCount() const;
	int GetPowerUpPosition(int) const;

	int GetScore() const;

	void UpdateTail();
	void UpdateBoard();
	void UpdateBlocks();
	void UpdateGameStatus();
	void UpdatePowerUps();
	void Update(int);

	bool IsGameOver() const;
	bool IsDead() const;
	void ResetGame();
	void RestartGame();

};

