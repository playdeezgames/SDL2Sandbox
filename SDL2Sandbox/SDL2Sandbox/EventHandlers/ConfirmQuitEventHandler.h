#pragma once
#include "JetLag2021EventHandler.h"

class ConfirmQuitEventHandler : public BaseEventHandler
{
private:
	int previousAxisState;
	bool& confirm;
	bool DoConfirmation();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	ConfirmQuitEventHandler(GameData&, bool&);
};

