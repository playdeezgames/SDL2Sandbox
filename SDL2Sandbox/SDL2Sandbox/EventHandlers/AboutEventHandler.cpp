#include "AboutEventHandler.h"
AboutEventHandler::AboutEventHandler(GameState& gameState)
	: BaseEventHandler(gameState)
{

}
bool AboutEventHandler::OnKeyDown(SDL_Keycode)
{
	SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool AboutEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool AboutEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

