#include "AboutEventHandler.h"
AboutEventHandler::AboutEventHandler(GameState& gameState, GameData& gameData)
	: BaseEventHandler(gameState, gameData)
{

}
bool AboutEventHandler::OnKeyDown(SDL_Keycode)
{
	GetGameData().SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool AboutEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	GetGameData().SetGameState(GameState::TITLE_SCREEN);
	return true;
}

bool AboutEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

