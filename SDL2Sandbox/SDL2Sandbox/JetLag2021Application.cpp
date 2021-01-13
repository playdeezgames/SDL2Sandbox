#include "JetLag2021Application.h"
#include "SDL_image.h"
#include "Utility.h"
#include "GameOverEventHandler.h"
#include "InPlayEventHandler.h"
JetLag2021Application JetLag2021Application::sandboxApplication;

JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, optionManager(soundManager)
	, gameData(soundManager)
	, renderer(gameData, soundManager)
	, joystick(nullptr)
	, eventHandlers()
{
}

void JetLag2021Application::Start()
{
	eventHandlers[GameState::GAME_OVER] = new GameOverEventHandler(gameData, soundManager, optionManager);
	eventHandlers[GameState::IN_PLAY] = new InPlayEventHandler(gameData);

	IMG_Init(IMG_INIT_PNG);
	optionManager.Load();
	renderer.Start(GetMainRenderer());

	soundManager.AddSound(Constants::Sound::CHOMP, Constants::Sound::CHOMP);
	soundManager.AddSound(Constants::Sound::DEATH, Constants::Sound::DEATH);
	soundManager.AddSound(Constants::Sound::TURN, Constants::Sound::TURN);
	soundManager.AddSound(Constants::Sound::TING, Constants::Sound::TING);
	soundManager.AddSound(Constants::Sound::CHARGE, Constants::Sound::CHARGE);
	soundManager.AddSound(Constants::Sound::WHOOPS, Constants::Sound::WHOOPS);
	soundManager.AddSound(Constants::Sound::BOOM, Constants::Sound::BOOM);
	soundManager.AddSound(Constants::Sound::YOINK, Constants::Sound::YOINK);
	soundManager.AddMusic(Constants::Sound::SONG, Constants::Sound::SONG);
	StartMusicWhenAppropriate();

	gameData.ResetGame();
	if (SDL_NumJoysticks() > 0)
	{
		joystick = SDL_JoystickOpen(0);
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

	soundManager.Finish();
	renderer.Finish();
	if (joystick)
	{
		SDL_JoystickClose(joystick);
		joystick = nullptr;
	}
	IMG_Quit();
}

bool JetLag2021Application::OnEvent(const SDL_Event& evt)
{
	return eventHandlers[gameData.GetGameState()]->OnEvent(evt);
}

void JetLag2021Application::Update(int milliseconds)
{
	gameData.Update(milliseconds);
}

void JetLag2021Application::Draw()
{
	renderer.Draw();
}

void JetLag2021Application::StartMusicWhenAppropriate()
{
	if (!soundManager.IsMuted())
	{
		soundManager.PlayMusic(Constants::Sound::SONG);
	}
}