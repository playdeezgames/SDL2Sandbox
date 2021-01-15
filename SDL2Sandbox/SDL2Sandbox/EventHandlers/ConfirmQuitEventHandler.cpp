#include "ConfirmQuitEventHandler.h"
ConfirmQuitEventHandler::ConfirmQuitEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}

bool ConfirmQuitEventHandler::OnKeyDown(SDL_Keycode)
{
	return true;
}

bool ConfirmQuitEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool ConfirmQuitEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}


