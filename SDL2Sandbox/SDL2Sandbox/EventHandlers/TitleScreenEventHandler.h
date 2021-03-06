#pragma once
#include "BaseEventHandler.h"
#include "..\Game\MainMenuItem.h"
class TitleScreenEventHandler : public BaseEventHandler
{
private:
	GameData& gameData;
	MainMenuItem& mainMenuItem;
	bool DoCurrentMainMenuItem();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
	void NextMainMenuItem();
	void PreviousMainMenuItem();
public:
	TitleScreenEventHandler(GameState&, GameData&, MainMenuItem&);
};

