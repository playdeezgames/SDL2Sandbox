#pragma once
#include "..\..\..\CommonCpp\Application.h"
class JetLag2021EventHandler : public tggd::common::EventHandler
{
protected:
	virtual bool OnKeyDown(SDL_Keycode) = 0;
	virtual bool OnJoyButtonDown(SDL_JoystickID, Uint8) = 0;
	virtual bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16) = 0;
public:
	bool OnEvent(const SDL_Event&);
};

