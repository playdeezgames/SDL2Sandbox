#pragma once
#include "JetLag2021EventHandler.h"
class InPlayEventHandler : public JetLag2021EventHandler
{
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
};

