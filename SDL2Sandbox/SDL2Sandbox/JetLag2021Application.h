#pragma once
#include "..\..\..\CommonCpp\Application.h"
#include "..\..\..\CommonCpp\SoundManager.h"
#include "Constants.h"
#include <vector>
#include <string>
#include "SDL_Mixer.h"
#include "GameData.h"
#include "OptionManager.h"
#include "JetLag2021Renderer.h"
#include <map>
class JetLag2021Application: public tggd::common::Application
{
private:
	std::map<GameState, tggd::common::EventHandler*> eventHandlers;
	static JetLag2021Application sandboxApplication;
	tggd::common::SoundManager soundManager;
	JetLag2021Renderer renderer;
	OptionManager optionManager;
	SDL_Joystick* joystick;

	GameData gameData;

	void StartMusicWhenAppropriate();//TODO: move me to option manager
protected:
	void Start();
	void Finish();
	void Update(int);
	void Draw();
public:
	bool OnEvent(const SDL_Event&);
	JetLag2021Application();
};

