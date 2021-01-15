#include "OptionsEventHandler.h"
OptionsEventHandler::OptionsEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}

bool OptionsEventHandler::OnKeyDown(SDL_Keycode)
{
	return true;
}

bool OptionsEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool OptionsEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

