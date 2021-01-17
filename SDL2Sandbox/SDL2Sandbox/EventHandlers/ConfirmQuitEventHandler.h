#pragma once
#include "BaseEventHandler.h"

class ConfirmQuitEventHandler : public BaseEventHandler
{
private:
	bool& confirm;
	bool DoConfirmation();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	ConfirmQuitEventHandler(GameState&, bool&);
};

