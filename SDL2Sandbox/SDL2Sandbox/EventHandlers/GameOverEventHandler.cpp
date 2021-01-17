#include "GameOverEventHandler.h"

const int FIRST_BUTTON = 0;

bool GameOverEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_SPACE:
		GetGameData().RestartGame();
		return true;
	case SDLK_ESCAPE:
		GetGameData().SetGameState(GameState::TITLE_SCREEN);
		return true;
	default:
		return true;
	}
}

bool GameOverEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8 button)
{
	switch (button)
	{
	case FIRST_BUTTON:
		GetGameData().RestartGame();
		return true;
	default:
		GetGameData().SetGameState(GameState::TITLE_SCREEN);
		return true;
	}
}

bool GameOverEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return true;
}

GameOverEventHandler::GameOverEventHandler(GameState& gameState, GameData& gameData)
	: BaseEventHandler(gameState, gameData)
{

}

