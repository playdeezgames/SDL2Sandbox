#pragma once
#include "JetLag2021EventHandler.h"

class ConfirmQuitEventHandler : public JetLag2021EventHandler
{
private:
	bool& confirm;
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	ConfirmQuitEventHandler(GameData&, bool&);
};

