#include "InstructionsEventHandler.h"
InstructionsEventHandler::InstructionsEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}

bool InstructionsEventHandler::OnKeyDown(SDL_Keycode)
{
	return true;
}

bool InstructionsEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool InstructionsEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

