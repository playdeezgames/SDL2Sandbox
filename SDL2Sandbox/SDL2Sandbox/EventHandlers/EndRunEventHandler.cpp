#include "EndRunEventHandler.h"

bool EndRunEventHandler::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE)
	{
		gameData.NextRun();
	}
	return true;
}

bool EndRunEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	gameData.NextRun();
	return true;
}

bool EndRunEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

EndRunEventHandler::EndRunEventHandler(GameState& gameState, GameData& gameData)
	: BaseEventHandler(gameState)
	, gameData(gameData)
{

}

