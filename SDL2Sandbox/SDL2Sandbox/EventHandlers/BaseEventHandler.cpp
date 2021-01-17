#include "BaseEventHandler.h"
bool BaseEventHandler::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		return OnKeyDown(evt.key.keysym.sym);
	case SDL_JOYBUTTONDOWN:
		return OnJoyButtonDown(evt.jbutton.which, evt.jbutton.button);
	case SDL_JOYAXISMOTION:
		return OnJoyAxisMotion(evt.jaxis.which, evt.jaxis.axis, evt.jaxis.value);
	default:
		return true;
	}
}

BaseEventHandler::BaseEventHandler(GameData& data)
	: gameData(data)
	, lastVertical(0)
	, vertical(0)
	, lastHorizontal(0)
	, horizontal(0)
{

}

GameData& BaseEventHandler::GetGameData() const
{
	return gameData;
}

bool BaseEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == 0)
	{
		lastHorizontal = horizontal;
		if (value < -8192)
		{
			horizontal = -1;
		}
		else if (value > 8192)
		{
			horizontal = 1;
		}
		else if (value<8192 && value>-8192)
		{
			horizontal = 0;
		}
	}
	if (axis == 1)
	{
		lastVertical = vertical;
		if (value < -8192)
		{
			vertical = -1;
		}
		else if (value > 8192)
		{
			vertical = 1;
		}
		else if (value<8192 && value>-8192)
		{
			vertical = 0;
		}
	}
	return true;
}

bool BaseEventHandler::IsVerticalUp() const
{
	return vertical == -1 && lastVertical != -1;
}

bool BaseEventHandler::IsVerticalDown() const
{
	return vertical == 1 && lastVertical != 1;
}

bool BaseEventHandler::IsHorizontalLeft() const
{
	return horizontal == -1 && lastHorizontal != -1;
}

bool BaseEventHandler::IsHorizontalRight() const
{
	return horizontal == 1 && lastHorizontal != 1;
}
