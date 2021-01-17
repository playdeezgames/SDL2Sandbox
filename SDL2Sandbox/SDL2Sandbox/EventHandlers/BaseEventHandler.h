#pragma once
#include "..\Common\Application.h"
#include "..\Game\GameData.h"
class BaseEventHandler : public tggd::common::EventHandler
{
private:
	int vertical;
	int lastVertical;
	int horizontal;
	int lastHorizontal;
	GameData& gameData;
	GameState& gameState;
protected:
	void SetGameState(const GameState&);
	bool IsVerticalUp() const;
	bool IsVerticalDown() const;
	bool IsHorizontalLeft() const;
	bool IsHorizontalRight() const;
	GameData& GetGameData() const;
	virtual bool OnKeyDown(SDL_Keycode) = 0;
	virtual bool OnJoyButtonDown(SDL_JoystickID, Uint8) = 0;
	virtual bool OnJoyAxisMotion(SDL_JoystickID, Uint8, Sint16);
public:
	BaseEventHandler(GameState&, GameData&);
	bool OnEvent(const SDL_Event&);
};

