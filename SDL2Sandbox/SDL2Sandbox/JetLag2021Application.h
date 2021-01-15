#pragma once
#include "Common\Application.h"
#include "Common\SoundManager.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "Game\GameData.h"
#include "OptionManager.h"
#include "Renderers\JetLag2021Renderer.h"
#include "RomFontManager.h"
#include <map>
class JetLag2021Application: public tggd::common::Application
{
private:
	std::map<GameState, tggd::common::EventHandler*> eventHandlers;
	std::map<GameState, tggd::common::Renderer*> renderers;
	static JetLag2021Application sandboxApplication;
	tggd::common::SoundManager soundManager;
	JetLag2021Renderer renderer;
	RomFontManager romFontManager;
	OptionManager optionManager;
	SDL_Joystick* joystick;
	SDL_GameController* controller;

	GameData gameData;

protected:
	void Start();
	void Finish();
	void Update(int);
public:
	void Draw();
	bool OnEvent(const SDL_Event&);
	JetLag2021Application();
};

