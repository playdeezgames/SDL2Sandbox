#include "AboutEventHandler.h"
AboutEventHandler::AboutEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}
bool AboutEventHandler::OnKeyDown(SDL_Keycode)
{
	return true;
}

bool AboutEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool AboutEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

