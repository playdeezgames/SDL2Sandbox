#include "TitleScreenEventHandler.h"
bool TitleScreenEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP:
		PreviousMainMenuItem();
		return true;
	case SDLK_DOWN:
		NextMainMenuItem();
		return true;
	case SDLK_SPACE:
		return DoCurrentMainMenuItem();
	default:
		return true;
	}
}

bool TitleScreenEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return DoCurrentMainMenuItem();
}

bool TitleScreenEventHandler::OnJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	BaseEventHandler::OnJoyAxisMotion(which, axis, value);
	if (IsVerticalDown())
	{
		NextMainMenuItem();
	}
	else if (IsVerticalUp())
	{
		PreviousMainMenuItem();
	}
	return true;
}

TitleScreenEventHandler::TitleScreenEventHandler(GameState& gameState, GameData& gameData, MainMenuItem& mainMenuItem)
	: BaseEventHandler(gameState)
	, mainMenuItem(mainMenuItem)
	, gameData(gameData)
{

}

bool TitleScreenEventHandler::DoCurrentMainMenuItem()
{
	switch (mainMenuItem)
	{
	case MainMenuItem::OPTIONS:
		SetGameState(GameState::OPTIONS);
		return true;
	case MainMenuItem::QUIT:
		SetGameState(GameState::CONFIRM_QUIT);
		return true;
	case MainMenuItem::PLAY:
		gameData.RestartGame();
		return true;
	case MainMenuItem::INSTRUCTIONS:
		SetGameState(GameState::INSTRUCTIONS);
		return true;
	case MainMenuItem::ABOUT:
		SetGameState(GameState::ABOUT);
		return true;
	default:
		return true;
	}
}

void TitleScreenEventHandler::NextMainMenuItem()
{
	switch (mainMenuItem)
	{
	case MainMenuItem::PLAY:
		mainMenuItem = MainMenuItem::INSTRUCTIONS;
		break;
	case MainMenuItem::INSTRUCTIONS:
		mainMenuItem = MainMenuItem::ABOUT;
		break;
	case MainMenuItem::ABOUT:
		mainMenuItem = MainMenuItem::OPTIONS;
		break;
	case MainMenuItem::OPTIONS:
		mainMenuItem = MainMenuItem::QUIT;
		break;
	case MainMenuItem::QUIT:
		mainMenuItem = MainMenuItem::PLAY;
		break;
	}
}

void TitleScreenEventHandler::PreviousMainMenuItem()
{
	switch (mainMenuItem)
	{
	case MainMenuItem::PLAY:
		mainMenuItem = MainMenuItem::QUIT;
		break;
	case MainMenuItem::INSTRUCTIONS:
		mainMenuItem = MainMenuItem::PLAY;
		break;
	case MainMenuItem::ABOUT:
		mainMenuItem = MainMenuItem::INSTRUCTIONS;
		break;
	case MainMenuItem::OPTIONS:
		mainMenuItem = MainMenuItem::ABOUT;
		break;
	case MainMenuItem::QUIT:
		mainMenuItem = MainMenuItem::OPTIONS;
		break;
	}
}
