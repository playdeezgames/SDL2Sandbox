#include "JetLag2021Application.h"
#include "SDL_image.h"
#include "Utility.h"
JetLag2021Application JetLag2021Application::sandboxApplication;

JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, optionManager(soundManager)
	, gameData(soundManager)
	, renderer(gameData, soundManager)
	, joystick(nullptr)
{
}

void JetLag2021Application::Start()
{

	IMG_Init(IMG_INIT_PNG);
	optionManager.Load();
	renderer.Start(GetMainRenderer());

	soundManager.Add(Constants::Sound::CHOMP, Constants::Sound::CHOMP);
	soundManager.Add(Constants::Sound::DEATH, Constants::Sound::DEATH);
	soundManager.Add(Constants::Sound::TURN, Constants::Sound::TURN);
	soundManager.Add(Constants::Sound::TING, Constants::Sound::TING);
	soundManager.Add(Constants::Sound::CHARGE, Constants::Sound::CHARGE);
	soundManager.Add(Constants::Sound::WHOOPS, Constants::Sound::WHOOPS);
	soundManager.Add(Constants::Sound::BOOM, Constants::Sound::BOOM);
	soundManager.Add(Constants::Sound::YOINK, Constants::Sound::YOINK);

	gameData.ResetGame();
	if (SDL_NumJoysticks() > 0)
	{
		joystick = SDL_JoystickOpen(0);
	}
}

void JetLag2021Application::Finish()
{
	soundManager.Finish();
	renderer.Finish();
	if (joystick)
	{
		SDL_JoystickClose(joystick);
		joystick = nullptr;
	}
	IMG_Quit();
}

bool JetLag2021Application::HandleInPlayKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_LEFT)
	{
		gameData.SetNextDirection(Constants::Game::Direction::LEFT);
	}
	else if (sym == SDLK_RIGHT)
	{
		gameData.SetNextDirection(Constants::Game::Direction::RIGHT);
	}
	else if (sym == SDLK_SPACE)
	{
		gameData.UseBomb();
	}
	return true;
}

bool JetLag2021Application::HandleGameOverKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE)
	{
		gameData.RestartGame();
	}
	else if (sym == SDLK_m)
	{
		soundManager.SetMuted(!soundManager.IsMuted());
		optionManager.Save();
	}
	return true;
}


bool JetLag2021Application::HandleKeyDown(SDL_Keycode sym)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayKeyDown(sym);
	}
	else
	{
		return HandleGameOverKeyDown(sym);
	}
}

bool JetLag2021Application::HandleInPlayJoyButtonDown(SDL_JoystickID which, Uint8 button)
{
	gameData.UseBomb();
	return true;
}

bool JetLag2021Application::HandleGameOverJoyButtonDown(SDL_JoystickID, Uint8)
{
	gameData.RestartGame();
	return true;
}


bool JetLag2021Application::HandleJoyButtonDown(SDL_JoystickID which, Uint8 button)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayJoyButtonDown(which, button);
	}
	else
	{
		return HandleGameOverJoyButtonDown(which, button);
	}
}

bool JetLag2021Application::HandleInPlayJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	if (axis == 0)
	{
		if (value <= -8192)
		{
			gameData.SetNextDirection(Constants::Game::Direction::LEFT);
		}
		else if (value >= 8192)
		{
			gameData.SetNextDirection(Constants::Game::Direction::RIGHT);
		}
	}
	return true;
}

bool JetLag2021Application::HandleGameOverJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	return true;
}


bool JetLag2021Application::HandleJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayJoyAxisMotion(which, axis, value);
	}
	else
	{
		return HandleGameOverJoyAxisMotion(which, axis, value);
	}
}

bool JetLag2021Application::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		return HandleKeyDown(evt.key.keysym.sym);
	case SDL_JOYBUTTONDOWN:
		return HandleJoyButtonDown(evt.jbutton.which, evt.jbutton.button);
	case SDL_JOYAXISMOTION:
		return HandleJoyAxisMotion(evt.jaxis.which, evt.jaxis.axis, evt.jaxis.value);
	default:
		return true;
	}
}

void JetLag2021Application::Update(int milliseconds)
{
	gameData.Update(milliseconds);
}


void JetLag2021Application::Draw()
{
	renderer.Draw();
}
