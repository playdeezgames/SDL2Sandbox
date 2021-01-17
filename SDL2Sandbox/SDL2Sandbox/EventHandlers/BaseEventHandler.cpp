#include "BaseEventHandler.h"
#include "..\Constants\Joystick.h"
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

BaseEventHandler::BaseEventHandler(GameState& gameState)
	: gameState(gameState)
	, lastVertical(0)
	, vertical(0)
	, lastHorizontal(0)
	, horizontal(0)
{

}

bool BaseEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8 axis, Sint16 value)
{
	if (axis == Constants::JoyStick::X_AXIS)
	{
		lastHorizontal = horizontal;
		if (value <= Constants::JoyStick::LOW_THRESHOLD)
		{
			horizontal = -1;
		}
		else if (value >= Constants::JoyStick::HIGH_THRESHOLD)
		{
			horizontal = 1;
		}
		else if (value<Constants::JoyStick::HIGH_THRESHOLD && value>Constants::JoyStick::LOW_THRESHOLD)
		{
			horizontal = 0;
		}
	}
	if (axis == Constants::JoyStick::Y_AXIS)
	{
		lastVertical = vertical;
		if (value <= Constants::JoyStick::LOW_THRESHOLD)
		{
			vertical = -1;
		}
		else if (value >= Constants::JoyStick::HIGH_THRESHOLD)
		{
			vertical = 1;
		}
		else if (value<Constants::JoyStick::HIGH_THRESHOLD && value>Constants::JoyStick::LOW_THRESHOLD)
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

void BaseEventHandler::SetGameState(const GameState& newState)
{
	gameState = newState;
}