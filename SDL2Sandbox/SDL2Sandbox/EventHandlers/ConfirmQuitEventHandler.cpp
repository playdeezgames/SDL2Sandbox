#include "ConfirmQuitEventHandler.h"
ConfirmQuitEventHandler::ConfirmQuitEventHandler(GameState& gameState, bool& confirm)
	: BaseEventHandler(gameState)
	, confirm(confirm)
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

bool ConfirmQuitEventHandler::OnJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	BaseEventHandler::OnJoyAxisMotion(which, axis, value);
	if (IsVerticalDown() || IsVerticalUp())
	{
		confirm = !confirm;
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
		SetGameState(GameState::TITLE_SCREEN);
		return true;
	}
}

