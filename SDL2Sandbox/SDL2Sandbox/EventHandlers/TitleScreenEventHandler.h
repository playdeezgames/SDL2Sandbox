#pragma once
#include "JetLag2021EventHandler.h"
class TitleScreenEventHandler : public JetLag2021EventHandler
{
private:
	int previousAxisState;
	bool DoCurrentMainMenuItem();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	TitleScreenEventHandler(GameData&);
};

