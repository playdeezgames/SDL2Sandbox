#include "OptionsEventHandler.h"
OptionsEventHandler::OptionsEventHandler(GameData& data, OptionsState& opt)
	: JetLag2021EventHandler(data)
	, state(opt)
{

}

bool OptionsEventHandler::DoOption()
{
	if (state == OptionsState::BACK)
	{
		GetGameData().SetGameState(GameState::TITLE_SCREEN);
	}
	return true;
}

bool OptionsEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_UP:
		PreviousOption();
		return true;
	case SDLK_DOWN:
		NextOption();
		return true;
	case SDLK_SPACE:
		return DoOption();
	default:
		return true;
	}
}

bool OptionsEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	return true;
}

bool OptionsEventHandler::OnJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	JetLag2021EventHandler::OnJoyAxisMotion(which, axis, value);
	if (IsVerticalDown())
	{
		NextOption();
	}
	if (IsVerticalUp())
	{
		PreviousOption();
	}
	return true;
}

void OptionsEventHandler::NextOption()
{
	switch (state)
	{
	case OptionsState::BACK:
		state = OptionsState::TOGGLE_MUTE;
		break;
	case OptionsState::TOGGLE_MUTE:
		state = OptionsState::SFX_VOLUME;
		break;
	case OptionsState::SFX_VOLUME:
		state = OptionsState::MUX_VOLUME;
		break;
	case OptionsState::MUX_VOLUME:
		state = OptionsState::BACK;
		break;
	}
}

void OptionsEventHandler::PreviousOption()
{
	switch (state)
	{
	case OptionsState::BACK:
		state = OptionsState::MUX_VOLUME;
		break;
	case OptionsState::TOGGLE_MUTE:
		state = OptionsState::BACK;
		break;
	case OptionsState::SFX_VOLUME:
		state = OptionsState::TOGGLE_MUTE;
		break;
	case OptionsState::MUX_VOLUME:
		state = OptionsState::SFX_VOLUME;
		break;
	}
}
