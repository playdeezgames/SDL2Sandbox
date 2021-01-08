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
	SDL_Rect romfontSrcRects[GameConstants::ROMFONT_CELL_COUNT];
	int counter;
	int direction;
	bool gameOver;
	int score;
	int runLength;
	bool muted;

	void ResetGame();
	void RestartGame();
	void DrawCharacter(int, int, char, const SDL_Color&);
	void DrawText(int, int, const std::string&, const SDL_Color&);
	void DrawCenteredText(int, const std::string&, const SDL_Color&);
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
	bool HandleInPlayKeyDown(SDL_Keycode);
	bool HandleGameOverKeyDown(SDL_Keycode);
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	SandboxApplication();
};

