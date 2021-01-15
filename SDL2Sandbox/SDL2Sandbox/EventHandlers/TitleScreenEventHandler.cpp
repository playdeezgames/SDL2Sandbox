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

bool TitleScreenEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == 1)
	{
		if (value < -8192 && previousAxisState!=-1)
		{
			previousAxisState = -1;
			GetGameData().PreviousMainMenuItem();
		}
		else if(value>8192 && previousAxisState!=1)
		{
			previousAxisState = 1;
			GetGameData().NextMainMenuItem();
		}
		else if(value<8192 && value>-8192 && previousAxisState!=0)
		{
			previousAxisState = 0;
		}
	}
	return true;
}

TitleScreenEventHandler::TitleScreenEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
	, previousAxisState(0)
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