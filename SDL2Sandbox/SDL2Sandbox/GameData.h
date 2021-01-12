#pragma once
#include <vector>
#include <map>
#include "..\..\..\CommonCpp\SoundManager.h"
enum class PowerUpType
{
	NONE,
	DIAMOND,
	PENNY,
	DOLLAR,
	POUND,
	YEN,
	INVINCIBLE,
	REVERSE_KEYS,
	BOMB
};
enum class PlayerState
{
	NORMAL,
	INVINCIBLE,
	INVINCIBILITY_WEARING_OFF,
	DEAD
};
struct PowerUp
{
	PowerUpType type;
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
	int invincibility;
	bool keysReversed;
	int bombs;

	static std::map<PowerUpType, int> powerUpGenerator;
	static PowerUpType GeneratePowerUp();
	static int GeneratePowerUpCounter();


	void UpdateTail();
	void UpdateBoard();
	void UpdateBlocks();
	void UpdateGameStatus();
	void UpdatePowerUps();


public:
	GameData(tggd::common::SoundManager&);
	void ResetGame();
	void RestartGame();
	void SetNextDirection(int);
	int GetTailLength() const;
	int GetTailPosition(int) const;

	int GetBlockCount() const;
	int GetBlockPosition(int) const;

	int GetPowerUpCount() const;
	int GetPowerUpPosition(int) const;
	PowerUpType GetPowerUp(int) const;

	int GetScore() const;

	bool IsGameOver() const;
	PlayerState GetState() const;
	void Update(int);
};

