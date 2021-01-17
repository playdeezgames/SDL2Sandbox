#pragma once
#include "BaseEventHandler.h"
#include "..\Game\OptionsState.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\OptionManager.h"
class OptionsEventHandler : public BaseEventHandler
{
private:
	tggd::common::SoundManager& soundManager;
	OptionManager& optionManager;
	OptionsState& state;
	void NextOption();
	void PreviousOption();
	void IncreaseOption();
	void DecreaseOption();
	void ChangeMuxVolume(int);
	void ChangeSfxVolume(int);
	bool DoOption();
protected:
	bool OnKeyDown(SDL_Keycode);
	bool OnJoyButtonDown(SDL_JoystickID, Uint8);
	bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	OptionsEventHandler(GameData&, OptionsState&, tggd::common::SoundManager&, OptionManager&);
};

