#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "..\..\..\CommonCpp\SoundManager.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "GameData.h"
#include "OptionManager.h"
#include "JetLag2021Renderer.h"
#include <map>
class JetLag2021Application: public tggd::common::Application
{
private:
	std::map<GameState, tggd::common::EventHandler*> eventHandlers;
	static JetLag2021Application sandboxApplication;
	tggd::common::SoundManager soundManager;
	JetLag2021Renderer renderer;
	OptionManager optionManager;
	SDL_Joystick* joystick;

	GameData gameData;

	void StartMusicWhenAppropriate();

	bool HandleKeyDown(SDL_Keycode);
	bool HandleInPlayKeyDown(SDL_Keycode);
	bool HandleGameOverKeyDown(SDL_Keycode);

	bool HandleJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleInPlayJoyButtonDown(SDL_JoystickID, Uint8);
	bool HandleGameOverJoyButtonDown(SDL_JoystickID, Uint8);

	bool HandleJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleInPlayJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	bool HandleGameOverJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
protected:
	void Start();
	void Finish();
	void Update(int);
	void Draw();
public:
	bool OnEvent(const SDL_Event&);
	JetLag2021Application();
};

