#pragma once
#include "JetLag2021EventHandler.h"
#include "..\Common\SoundManager.h"
#include "..\OptionManager.h"
class GameOverEventHandler : public JetLag2021EventHandler
{
private:
	tggd::common::SoundManager& soundManager;
	OptionManager& optionManager;
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	GameOverEventHandler(GameData&, tggd::common::SoundManager&, OptionManager&);
};
