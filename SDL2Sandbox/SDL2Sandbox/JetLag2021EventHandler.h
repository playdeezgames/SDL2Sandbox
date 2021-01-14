#pragma once
#include "Common\Application.h"
#include "Game/GameData.h"
class JetLag2021EventHandler : public tggd::common::EventHandler
{
private:
	GameData& gameData;
protected:
	GameData& GetGameData() const;
	virtual bool OnKeyDown(SDL_Keycode) = 0;
	virtual bool OnJoyButtonDown(SDL_JoystickID, Uint8) = 0;
	virtual bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16) = 0;
public:
	JetLag2021EventHandler(GameData&);
	bool OnEvent(const SDL_Event&);
};

