#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "SoundManager.h"
class JetLag2021Application: public tggd::common::Application
{
private:
	tggd::common::SoundManager soundManager;
	SDL_Texture* romfontTexture;
	SDL_Joystick* joystick;

	static JetLag2021Application sandboxApplication;
	std::vector<int> blocks;
	std::vector<int> pickUps;
	std::vector<int> tail;
	SDL_Rect romfontSrcRects[Constants::RomFont::CELL_COUNT];
	int counter;
	int direction;
	bool gameOver;
	int score;
	int runLength;
	bool muted;
	bool dead;

	void ResetGame();
	void RestartGame();
	void SetNextDirection(int);

	void DrawCharacter(int, int, char, const SDL_Color&);
	void DrawText(int, int, const std::string&, const SDL_Color&);
	void DrawCenteredText(int, const std::string&, const SDL_Color&);
	void DrawBackground();
	void DrawTail();
	void DrawBlocks();
	void DrawPickUps();
	void DrawWalls();
	void DrawScore();
	void DrawHints();
	void DrawMuteHint();
	void DrawStartHint();

	void PlaySound(const std::string&);

	void LoadOptions();
	void SaveOptions();

	void UpdateBoard();
	void UpdateTail();
	void UpdateBlocks();
	void UpdateGameStatus();
	void UpdatePickUps();

	bool HandleKeyDown(SDL_Keycode);
	bool HandleInPlayKeyDown(SDL_Keycode);
	bool HandleGameOverKeyDown(SDL_Keycode);
	bool HandleInPlayJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleGameOverJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleInPlayJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleGameOverJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);

	static void PlotCellRect(SDL_Rect&, int, int);
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	JetLag2021Application();
};

