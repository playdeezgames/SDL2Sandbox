#pragma once
#include "Application.h"
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

	void ResetGame();
	void RestartGame();
	void DrawText(int, int, const std::string&, Uint8, Uint8, Uint8);
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	SandboxApplication();
};

