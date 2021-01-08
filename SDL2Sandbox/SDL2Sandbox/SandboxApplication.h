#pragma once
#include "Application.h"
#include "GameConstants.h"
#include <vector>
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

	void ResetGame();
	void RestartGame();
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	SandboxApplication();
};

