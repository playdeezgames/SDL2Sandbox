#pragma once
#include "JetLag2021EventHandler.h"
class EndRunEventHandler : public BaseEventHandler
{
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	EndRunEventHandler(GameData&);
};

