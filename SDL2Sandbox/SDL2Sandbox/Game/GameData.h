#pragma once
#include <vector>
#include <map>
#include "..\Common\SoundManager.h"
#include "PlayerState.h"
#include "PowerUp.h"
#include "GameState.h"
class GameData
{
private:
	const tggd::common::SoundManager& soundManager;
	GameState& gameState;

	std::vector<int> blockPositions;
	std::vector<PowerUp> powerUpPositions;
	std::vector<int> tailPositions;

	int powerUpCounter;
	int scrollCounter;
	int scrollCounterMaximum;

	int score;
	int runLength;
	int scoreMultiplier;
	int scoreDivisor;
	
	int direction;
	bool dead;
	int invincibility;
	bool keysReversed;
	int bombs;
	int lives;
	int shield;

	static std::map<PowerUpType, int> powerUpGenerator;
	static PowerUpType GeneratePowerUp();
	static int GeneratePowerUpCounter();

	void UpdateTail();
	void UpdateBoard();
	void UpdateBlocks();
	void UpdateGameStatus();
	void UpdatePowerUps();
	void ResetRun();
	void AddScore(int);
public:
	GameData(tggd::common::SoundManager&, GameState&);

	void ResetGame();
	void RestartGame();
	void NextRun();

	void SetNextDirection(int);

	int GetTailLength() const;
	int GetTailPosition(int) const;

	int GetBlockCount() const;
	int GetBlockPosition(int) const;

	int GetPowerUpCount() const;
	int GetPowerUpPosition(int) const;
	PowerUpType GetPowerUp(int) const;

	PlayerState GetState() const;

	int GetScore() const;
	int GetScoreMultiplier() const;
	int GetScoreDivisor() const;

	void Update(int);

	void UseBomb();
	int GetBombs() const;

	void LoseLife();
	int GetLives() const;

	int GetShield() const;
};

