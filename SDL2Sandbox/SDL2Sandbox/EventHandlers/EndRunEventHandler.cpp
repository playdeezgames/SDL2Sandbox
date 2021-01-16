#include "EndRunEventHandler.h"

bool EndRunEventHandler::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE)
	{
		GetGameData().NextRun();
	}
	return true;
}

bool EndRunEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	GetGameData().NextRun();
	return true;
}

bool EndRunEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

EndRunEventHandler::EndRunEventHandler(GameData& gameData)
	: JetLag2021EventHandler(gameData)
{

}

