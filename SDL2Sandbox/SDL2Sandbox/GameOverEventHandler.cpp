#include "GameOverEventHandler.h"
#include "Constants.h"
bool GameOverEventHandler::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE)
	{
		GetGameData().RestartGame();
	}
	else if (sym == SDLK_m)
	{
		soundManager.SetMuted(!soundManager.IsMuted());
		optionManager.Save();
		if (!soundManager.IsMuted())
		{
			soundManager.PlayMusic(Constants::Sound::SONG);
		}

	}
	return true;

}

bool GameOverEventHandler::OnJoyButtonDown(SDL_JoystickID, Uint8)
{
	GetGameData().RestartGame();
	return true;
}

bool GameOverEventHandler::OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16)
{
	return false;
}

GameOverEventHandler::GameOverEventHandler(GameData& data, tggd::common::SoundManager& sndMan, OptionManager& optMan)
	: JetLag2021EventHandler(data)
	, soundManager(sndMan)
	, optionManager(optMan)
{

}

