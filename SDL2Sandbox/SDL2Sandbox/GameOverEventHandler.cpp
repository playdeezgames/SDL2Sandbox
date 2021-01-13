#include "GameOverEventHandler.h"
bool GameOverEventHandler::OnKeyDown(SDL_Keycode)
{
	return false;
}

bool GameOverEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return false;
}

bool GameOverEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return false;
}

