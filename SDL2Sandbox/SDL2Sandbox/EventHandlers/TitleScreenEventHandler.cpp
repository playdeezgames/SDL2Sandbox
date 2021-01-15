#include "TitleScreenEventHandler.h"
bool TitleScreenEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
		case SDLK_UP:
			GetGameData().PreviousMainMenuItem();
			break;
		case SDLK_DOWN:
			GetGameData().NextMainMenuItem();
			break;
		case SDLK_SPACE:
			return DoCurrentMainMenuItem();
	}
	return true;
}

bool TitleScreenEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return DoCurrentMainMenuItem();
}

bool TitleScreenEventHandler::OnJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	JetLag2021EventHandler::OnJoyAxisMotion(which, axis, value);
	if (IsVerticalDown())
	{
		GetGameData().NextMainMenuItem();
	}
	if (IsVerticalUp())
	{
		GetGameData().PreviousMainMenuItem();
	}
	return true;
}

TitleScreenEventHandler::TitleScreenEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}

bool TitleScreenEventHandler::DoCurrentMainMenuItem()
{
	switch (GetGameData().GetMainMenuItem())
	{
	case MainMenuItem::QUIT:
		GetGameData().SetGameState(GameState::CONFIRM_QUIT);
		return true;
	case MainMenuItem::PLAY:
		GetGameData().RestartGame();
		return true;
	default:
		return true;
	}
}