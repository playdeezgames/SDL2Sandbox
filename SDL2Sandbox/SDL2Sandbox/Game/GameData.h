#pragma once
#include <vector>
#include <map>
#include "..\Common\SoundManager.h"
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
	BOMB,
	EXTRA_LIFE,
	SCORE_NORMAL,
	SCORE_DOUBLE,
	SCORE_QUADRUPAL,
	SCORE_HALF,
	SCORE_QUARTER,
	SPEED_UP, //18
	SLOW_DOWN //19
};
enum class PlayerState
{
	NORMAL,
	INVINCIBLE,
	INVINCIBILITY_WEARING_OFF,
	DEAD
};
enum class GameState
{
	GAME_OVER,
	IN_PLAY,
	TITLE_SCREEN,
	INSTRUCTIONS,
	ABOUT,
	OPTIONS,
	CONFIRM_QUIT,
	END_RUN
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
	GameState& gameState;
	int score;
	int runLength;
	bool dead;
	int invincibility;
	bool keysReversed;
	int bombs;
	int lives;
	int scoreMultiplier;
	int scoreDivisor;
	int scrollCounterMaximum;

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
	int GetScore() const;
	GameState GetGameState() const;
	PlayerState GetState() const;
	void Update(int);
	void UseBomb();
	int GetBombs() const;
	void LoseLife();
	int GetLives() const;
	void SetGameState(const GameState&);
	int GetScoreMultiplier() const;
	int GetScoreDivisor() const;
};

