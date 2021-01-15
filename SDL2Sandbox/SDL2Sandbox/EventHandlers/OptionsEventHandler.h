#pragma once
#include "JetLag2021EventHandler.h"
#include "..\Game\OptionsState.h"
class OptionsEventHandler : public JetLag2021EventHandler
{
private:
	OptionsState& state;
	void NextOption();
	void PreviousOption();
	bool DoOption();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	OptionsEventHandler(GameData&, OptionsState&);
};

