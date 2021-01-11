#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "..\..\..\CommonCpp\SoundManager.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "GameData.h"
class JetLag2021Application: public tggd::common::Application
{
private:
	tggd::common::SoundManager soundManager;
	SDL_Texture* romfontTexture;
	SDL_Joystick* joystick;
	static JetLag2021Application sandboxApplication;

	GameData gameData;
	SDL_Rect romfontSrcRects[Constants::RomFont::CELL_COUNT];

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

	void LoadOptions();
	void SaveOptions();


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

