#include "InPlayEventHandler.h"
#include "Constants\Game.h"
bool InPlayEventHandler::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_LEFT)
	{
		GetGameData().SetNextDirection(Constants::Game::Direction::LEFT);
	}
	else if (sym == SDLK_RIGHT)
	{
		GetGameData().SetNextDirection(Constants::Game::Direction::RIGHT);
	}
	else if (sym == SDLK_SPACE)
	{
		GetGameData().UseBomb();
	}
	return true;
}

bool InPlayEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	GetGameData().UseBomb();
	return true;
}

bool InPlayEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == 0)
	{
		if (value <= -8192)
		{
			GetGameData().SetNextDirection(Constants::Game::Direction::LEFT);
		}
		else if (value >= 8192)
		{
			GetGameData().SetNextDirection(Constants::Game::Direction::RIGHT);
		}
	}
	return true;
}

InPlayEventHandler::InPlayEventHandler(GameData& data)
	: JetLag2021EventHandler(data)
{

}


