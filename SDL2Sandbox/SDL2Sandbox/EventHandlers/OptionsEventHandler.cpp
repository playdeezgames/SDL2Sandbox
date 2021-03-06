#include "OptionsEventHandler.h"
#include "..\Constants\Sound.h"
const int VOLUME_DELTA = 8;
const int MINIMUM_VOLUME = 0;
const int MAXIMUM_VOLUME = 128;

OptionsEventHandler::OptionsEventHandler
	(
		GameState& gameState,
		OptionsState& optionsState, 
		tggd::common::SoundManager& soundManager,
		OptionManager& optionManager
	)
	: BaseEventHandler(gameState)
	, state(optionsState)
	, soundManager(soundManager)
	, optionManager(optionManager)
{

}

bool OptionsEventHandler::DoOption()
{
	switch(state)
	{
	case OptionsState::BACK:
		optionManager.Save();
		SetGameState(GameState::TITLE_SCREEN);
		return true;
	case OptionsState::TOGGLE_MUTE:
		soundManager.SetMuted(!soundManager.IsMuted());
		if (!soundManager.IsMuted())
		{
			soundManager.PlayMusic(Constants::Sound::Name::SONG);
		}
		return true;
	default:
		return true;
	}
}

bool OptionsEventHandler::OnKeyDown(SDL_Keycode sym)
{
	switch (sym)
	{
	case SDLK_LEFT:
		DecreaseOption();
		return true;
	case SDLK_RIGHT:
		IncreaseOption();
		return true;
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
	DoOption();
	return true;
}

bool OptionsEventHandler::OnJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	BaseEventHandler::OnJoyAxisMotion(which, axis, value);
	if (IsHorizontalLeft())
	{
		DecreaseOption();
	}
	else if (IsHorizontalRight())
	{
		IncreaseOption();
	}
	else if (IsVerticalDown())
	{
		NextOption();
	}
	else if (IsVerticalUp())
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

void OptionsEventHandler::IncreaseOption()
{
	switch (state)
	{
	case OptionsState::MUX_VOLUME:
		ChangeMuxVolume(VOLUME_DELTA);
		break;
	case OptionsState::SFX_VOLUME:
		ChangeSfxVolume(VOLUME_DELTA);
		break;
	}
}

void OptionsEventHandler::DecreaseOption()
{
	switch (state)
	{
	case OptionsState::MUX_VOLUME:
		ChangeMuxVolume(-VOLUME_DELTA);
		break;
	case OptionsState::SFX_VOLUME:
		ChangeSfxVolume(-VOLUME_DELTA);
		break;
	}
}

static int ClampVolume(int volume)
{
	return 		
		(volume < MINIMUM_VOLUME) ? (MINIMUM_VOLUME) :
		(volume > MAXIMUM_VOLUME) ? (MAXIMUM_VOLUME) :
		volume;
}

void OptionsEventHandler::ChangeMuxVolume(int delta)
{
	soundManager.SetMuxVolume(ClampVolume(soundManager.GetMuxVolume() + delta));
}

void OptionsEventHandler::ChangeSfxVolume(int delta)
{
	soundManager.SetSfxVolume(ClampVolume(soundManager.GetSfxVolume() + delta));
	soundManager.PlaySound(Constants::Sound::Name::TURN);
}
