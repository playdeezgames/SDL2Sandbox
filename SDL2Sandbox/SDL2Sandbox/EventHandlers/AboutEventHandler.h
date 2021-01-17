#pragma once
#include "BaseEventHandler.h"

class AboutEventHandler : public BaseEventHandler
{
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	AboutEventHandler(GameState&, GameData&);
};

