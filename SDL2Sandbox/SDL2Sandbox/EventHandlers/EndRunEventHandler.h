#pragma once
#include "BaseEventHandler.h"
class EndRunEventHandler : public BaseEventHandler
{
private:
	GameData& gameData;
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	EndRunEventHandler(GameState&, GameData&);
};

