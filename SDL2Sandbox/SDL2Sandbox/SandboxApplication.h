#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "GameConstants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
class SandboxApplication: public Application
{
private:
	Mix_Chunk* turnSound;
	Mix_Chunk* deathSound;
	SDL_Texture* romfontTexture;

	static SandboxApplication sandboxApplication;
	std::vector<int> blocks;
	std::vector<int> tail;
	int counter;
	int direction;
	bool gameOver;
	int score;
	int runLength;
	bool muted;

	void ResetGame();
	void RestartGame();
	void DrawText(int, int, const std::string&, Uint8, Uint8, Uint8);
	void DrawCenteredText(int, const std::string&, Uint8, Uint8, Uint8);
	void PlaySound(Mix_Chunk*);
	void LoadOptions();
	void SaveOptions();
	void SetNextDirection(int);
	void DrawBackground();
	void DrawTail();
	void DrawBlocks();
	void DrawWalls();
	void DrawScore();
	void DrawHints();
	void DrawMuteHint();
	void DrawStartHint();
	void UpdateBoard();
	void UpdateTail();
	void UpdateBlocks();
	void CheckForGameOver();
	bool HandleKeyDown(SDL_Keycode);
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	SandboxApplication();
};

