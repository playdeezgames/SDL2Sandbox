#pragma once
#include "BaseEventHandler.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\OptionManager.h"
class GameOverEventHandler : public BaseEventHandler
{
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	GameOverEventHandler(GameData&);
};
