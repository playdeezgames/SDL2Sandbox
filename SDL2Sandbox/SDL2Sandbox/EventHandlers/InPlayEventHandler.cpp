#include "InPlayEventHandler.h"
#include "..\Constants\Game.h"
#include "..\Constants\Joystick.h"
bool InPlayEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_LEFT:
		gameData.SetNextDirection(Constants::Game::Direction::LEFT);
		return true;
	case SDLK_RIGHT:
		gameData.SetNextDirection(Constants::Game::Direction::RIGHT);
		return true;
	case SDLK_SPACE:
		gameData.UseBomb();
		return true;
	default:
		return true;
	}
}

bool InPlayEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	gameData.UseBomb();
	return true;
}

bool InPlayEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == Constants::JoyStick::X_AXIS)
	{
		if (value <= Constants::JoyStick::LOW_THRESHOLD)
		{
			gameData.SetNextDirection(Constants::Game::Direction::LEFT);
		}
		else if (value >= Constants::JoyStick::HIGH_THRESHOLD)
		{
			gameData.SetNextDirection(Constants::Game::Direction::RIGHT);
		}
	}
	return true;
}

InPlayEventHandler::InPlayEventHandler(GameState& gameState, GameData& gameData)
	: BaseEventHandler(gameState)
	, gameData(gameData)
{
}


