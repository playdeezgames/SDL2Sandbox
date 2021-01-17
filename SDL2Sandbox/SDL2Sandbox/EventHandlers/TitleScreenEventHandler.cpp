#include "TitleScreenEventHandler.h"
bool TitleScreenEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP:
		GetGameData().PreviousMainMenuItem();
		return true;
	case SDLK_DOWN:
		GetGameData().NextMainMenuItem();
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
		GetGameData().NextMainMenuItem();
	}
	else if (IsVerticalUp())
	{
		GetGameData().PreviousMainMenuItem();
	}
	return true;
}

TitleScreenEventHandler::TitleScreenEventHandler(GameData& data)
	: BaseEventHandler(data)
{

}

bool TitleScreenEventHandler::DoCurrentMainMenuItem()
{
	switch (GetGameData().GetMainMenuItem())
	{
	case MainMenuItem::OPTIONS:
		GetGameData().SetGameState(GameState::OPTIONS);
		return true;
	case MainMenuItem::QUIT:
		GetGameData().SetGameState(GameState::CONFIRM_QUIT);
		return true;
	case MainMenuItem::PLAY:
		GetGameData().RestartGame();
		return true;
	case MainMenuItem::INSTRUCTIONS:
		GetGameData().SetGameState(GameState::INSTRUCTIONS);
		return true;
	case MainMenuItem::ABOUT:
		GetGameData().SetGameState(GameState::ABOUT);
		return true;
	default:
		return true;
	}
}