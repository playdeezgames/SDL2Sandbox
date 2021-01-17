#include "InstructionsEventHandler.h"
InstructionsEventHandler::InstructionsEventHandler(GameState& gameState, GameData& gameData)
	: BaseEventHandler(gameState, gameData)
{

}

bool InstructionsEventHandler::OnKeyDown(SDL_Keycode)
{
	GetGameData().SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool InstructionsEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	GetGameData().SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool InstructionsEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

