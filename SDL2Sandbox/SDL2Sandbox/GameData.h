#pragma once
#include <vector>
class GameData
{
private:
	std::vector<int> blocks;
	std::vector<int> pickUps;
	std::vector<int> tail;
	int counter;
	int direction;
	bool gameOver;
	int score;
	int runLength;
	bool dead;
public:
	GameData();
	bool SetNextDirection(int);
	bool IsGameOver() const;
	int GetTailLength() const;
	int GetTailPosition(int) const;
	bool IsDead() const;
	int GetBlockCount() const;
	int GetBlockPosition(int) const;
	int GetPickUpCount() const;
	int GetPickUpPosition(int) const;
	int GetScore() const;
	void UpdateTail();
	void UpdateBoard();
	void UpdateBlocks();
	void UpdateGameStatus();
	void UpdatePickUps();
	void Update(int);
	void ResetGame();
	void RestartGame();

};

