#include "TitleScreenEventHandler.h"
bool TitleScreenEventHandler::OnKeyDown(SDL_Keycode)
{
	return true;
}

bool TitleScreenEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool TitleScreenEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

TitleScreenEventHandler::TitleScreenEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}

