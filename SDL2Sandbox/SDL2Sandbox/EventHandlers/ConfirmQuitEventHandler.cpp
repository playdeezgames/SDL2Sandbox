#include "ConfirmQuitEventHandler.h"
ConfirmQuitEventHandler::ConfirmQuitEventHandler(GameData& data, bool& conf)
	: JetLag2021EventHandler(data)
	, confirm(conf)
	, previousAxisState(0)
{

}

bool ConfirmQuitEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_SPACE:
		return DoConfirmation();
	case SDLK_UP:
	case SDLK_DOWN:
		confirm = !confirm;
		return true;
	default:
		return true;
	}
}

bool ConfirmQuitEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return DoConfirmation();
}

bool ConfirmQuitEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == 1)
	{
		if (value < -8192 && previousAxisState != -1)
		{
			previousAxisState = -1;
			confirm = !confirm;
		}
		else if (value > 8192 && previousAxisState != 1)
		{
			previousAxisState = 1;
			confirm = !confirm;
		}
		else if (value<8192 && value>-8192 && previousAxisState != 0)
		{
			previousAxisState = 0;
		}
	}
	return true;
}

bool ConfirmQuitEventHandler::DoConfirmation()
{
	if (confirm)
	{
		return false;
	}
	else
	{
		GetGameData().SetGameState(GameState::TITLE_SCREEN);
		return true;
	}
}

