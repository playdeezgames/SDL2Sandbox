#include "InstructionsEventHandler.h"
InstructionsEventHandler::InstructionsEventHandler(GameState& gameState)
	: BaseEventHandler(gameState)
{

}

bool InstructionsEventHandler::OnKeyDown(SDL_Keycode)
{
	SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool InstructionsEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool InstructionsEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

