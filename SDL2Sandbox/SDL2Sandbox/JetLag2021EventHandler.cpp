#include "JetLag2021EventHandler.h"
bool JetLag2021EventHandler::OnEvent(const SDL_Event& evt)
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

JetLag2021EventHandler::JetLag2021EventHandler(GameData& data)
	: gameData(data)
{

}

GameData& JetLag2021EventHandler::GetGameData() const
{
	return gameData;
}