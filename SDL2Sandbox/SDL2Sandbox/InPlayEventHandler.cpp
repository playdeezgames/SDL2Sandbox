#include "InPlayEventHandler.h"
bool InPlayEventHandler::OnKeyDown(SDL_Keycode)
{
	return false;
}

bool InPlayEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return false;
}

bool InPlayEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return false;
}

