#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "..\..\..\CommonCpp\SoundManager.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "GameData.h"
#include "OptionManager.h"
#include "Renderer.h"
class JetLag2021Application: public tggd::common::Application
{
private:
	static JetLag2021Application sandboxApplication;
	tggd::common::SoundManager soundManager;
	Renderer renderer;
	OptionManager optionManager;
	SDL_Joystick* joystick;

	GameData gameData;

	bool HandleKeyDown(SDL_Keycode);
	bool HandleInPlayKeyDown(SDL_Keycode);
	bool HandleGameOverKeyDown(SDL_Keycode);
	bool HandleInPlayJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleGameOverJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleInPlayJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleGameOverJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);

protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	JetLag2021Application();
};

