#include "JetLag2021Application.h"
#include <SDL_image.h>

#include "Constants\Sound.h"
#include "Constants\Window.h"

#include "EventHandlers\AboutEventHandler.h"
#include "EventHandlers\ConfirmQuitEventHandler.h"
#include "EventHandlers\EndRunEventHandler.h"
#include "EventHandlers\GameOverEventHandler.h"
#include "EventHandlers\InPlayEventHandler.h"
#include "EventHandlers\InstructionsEventHandler.h"
#include "EventHandlers\OptionsEventHandler.h"
#include "EventHandlers\TitleScreenEventHandler.h"

#include "Renderers\AboutRenderer.h"
#include "Renderers\ConfirmQuitRenderer.h"
#include "Renderers\GameOverRenderer.h"
#include "Renderers\InstructionsRenderer.h"
#include "Renderers\OptionsRenderer.h"
#include "Renderers\TitleScreenRenderer.h"

#include "Utility.h"

JetLag2021Application JetLag2021Application::sandboxApplication;
JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, optionManager(soundManager)
	, gameState(GameState::TITLE_SCREEN)
	, gameData(soundManager, gameState)
	, romFontManager()
	, renderer(gameData, soundManager, romFontManager)
	, joystick(nullptr)
	, eventHandlers()
	, controller(nullptr)
	, renderers()
	, confirmQuit(false)
	, optionsState(OptionsState::BACK)
	, mainMenuItem(MainMenuItem::PLAY)
{
}

void JetLag2021Application::Start()
{
	eventHandlers[GameState::GAME_OVER] = new GameOverEventHandler(gameState, gameData);
	eventHandlers[GameState::IN_PLAY] = new InPlayEventHandler(gameState, gameData);
	eventHandlers[GameState::TITLE_SCREEN] = new TitleScreenEventHandler(gameState, gameData, mainMenuItem);
	eventHandlers[GameState::INSTRUCTIONS] = new InstructionsEventHandler(gameState);
	eventHandlers[GameState::CONFIRM_QUIT] = new ConfirmQuitEventHandler(gameState, confirmQuit);
	eventHandlers[GameState::ABOUT] = new AboutEventHandler(gameState);
	eventHandlers[GameState::OPTIONS] = new OptionsEventHandler(gameState, optionsState, soundManager, optionManager);
	eventHandlers[GameState::END_RUN] = new EndRunEventHandler(gameState, gameData);

	renderers[GameState::GAME_OVER] = new GameOverRenderer(GetMainRenderer(), romFontManager);
	renderers[GameState::TITLE_SCREEN] = new TitleScreenRenderer(GetMainRenderer(), soundManager, romFontManager, mainMenuItem);
	renderers[GameState::CONFIRM_QUIT] = new ConfirmQuitRenderer(GetMainRenderer(), romFontManager, confirmQuit);
	renderers[GameState::ABOUT] = new AboutRenderer(GetMainRenderer(), romFontManager);
	renderers[GameState::INSTRUCTIONS] = new InstructionsRenderer(GetMainRenderer(), romFontManager);
	renderers[GameState::OPTIONS] = new OptionsRenderer(GetMainRenderer(), romFontManager, optionsState, soundManager);

	IMG_Init(IMG_INIT_PNG);
	romFontManager.Start(GetMainRenderer());
	renderer.Start(GetMainRenderer());

	soundManager.AddSound(Constants::Sound::Name::CHOMP, Constants::Sound::FileName::CHOMP);
	soundManager.AddSound(Constants::Sound::Name::DEATH, Constants::Sound::FileName::DEATH);
	soundManager.AddSound(Constants::Sound::Name::TURN, Constants::Sound::FileName::TURN);
	soundManager.AddSound(Constants::Sound::Name::TING, Constants::Sound::FileName::TING);
	soundManager.AddSound(Constants::Sound::Name::CHARGE, Constants::Sound::FileName::CHARGE);
	soundManager.AddSound(Constants::Sound::Name::WHOOPS, Constants::Sound::FileName::WHOOPS);
	soundManager.AddSound(Constants::Sound::Name::BOOM, Constants::Sound::FileName::BOOM);
	soundManager.AddSound(Constants::Sound::Name::YOINK, Constants::Sound::FileName::YOINK);
	soundManager.AddSound(Constants::Sound::Name::NOPE, Constants::Sound::FileName::NOPE);
	soundManager.AddSound(Constants::Sound::Name::WOOHOO, Constants::Sound::FileName::WOOHOO);
	soundManager.AddSound(Constants::Sound::Name::SPEEDUP, Constants::Sound::FileName::SPEEDUP);
	soundManager.AddSound(Constants::Sound::Name::SLOWDOWN, Constants::Sound::FileName::SLOWDOWN);
	soundManager.AddSound(Constants::Sound::Name::NORMALSPEED, Constants::Sound::FileName::NORMALSPEED);

	soundManager.AddMusic(Constants::Sound::Name::SONG, Constants::Sound::FileName::SONG);

	optionManager.Load();//timing! must happen after sounds are loaded, because it plays music

	gameData.ResetGame();
	if (SDL_NumJoysticks() > 0)
	{
		controller = SDL_GameControllerOpen(0);
		if (!controller)
		{
			joystick = SDL_JoystickOpen(0);
		}
	}
}

void JetLag2021Application::Finish()
{
	for (auto& entry : eventHandlers)
	{
		if (entry.second)
		{
			delete entry.second;
			entry.second = nullptr;
		}
	}
	eventHandlers.clear();
	for (auto& entry : renderers)
	{
		if (entry.second)
		{
			delete entry.second;
			entry.second = nullptr;
		}
	}
	renderers.clear();

	soundManager.Finish();
	renderer.Finish();
	romFontManager.Finish();
	if (joystick)
	{
		SDL_JoystickClose(joystick);
		joystick = nullptr;
	}
	if (controller)
	{
		SDL_GameControllerClose(controller);
		controller = nullptr;
	}
	IMG_Quit();
}

bool JetLag2021Application::OnEvent(const SDL_Event& evt)
{
	bool result = eventHandlers[gameState]->OnEvent(evt);
	if (!result)
	{
		SDL_Log("wat");
	}
	return result;
}

void JetLag2021Application::Update(int milliseconds)
{
	gameData.Update(milliseconds);
}

void JetLag2021Application::Draw()
{
	renderer.Draw();
	auto stateRenderer = renderers.find(gameState);
	if (stateRenderer != renderers.end())
	{
		stateRenderer->second->Draw();
	}
}

