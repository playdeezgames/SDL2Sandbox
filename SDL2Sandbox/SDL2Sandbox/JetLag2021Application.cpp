#include "JetLag2021Application.h"
#include "SDL_image.h"
#include "Utility.h"
#include "GameOverEventHandler.h"
#include "InPlayEventHandler.h"
#include "GameOverRenderer.h"
#include "TitleScreenEventHandler.h"
#include "TitleScreenRenderer.h"
JetLag2021Application JetLag2021Application::sandboxApplication;

JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, optionManager(soundManager)
	, gameData(soundManager)
	, romFontManager()
	, renderer(gameData, soundManager, romFontManager)
	, joystick(nullptr)
	, eventHandlers()
	, controller(nullptr)
	, renderers()
{
}

void JetLag2021Application::Start()
{
	eventHandlers[GameState::GAME_OVER] = new GameOverEventHandler(gameData, soundManager, optionManager);
	eventHandlers[GameState::IN_PLAY] = new InPlayEventHandler(gameData);
	eventHandlers[GameState::TITLE_SCREEN] = new TitleScreenEventHandler(gameData);

	renderers[GameState::GAME_OVER] = new GameOverRenderer(GetMainRenderer(), soundManager, romFontManager, gameData);
	renderers[GameState::TITLE_SCREEN] = new TitleScreenRenderer(GetMainRenderer());

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
	bool result = eventHandlers[gameData.GetGameState()]->OnEvent(evt);
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
	auto stateRenderer = renderers.find(gameData.GetGameState());
	if (stateRenderer != renderers.end())
	{
		stateRenderer->second->Draw();
	}

}

