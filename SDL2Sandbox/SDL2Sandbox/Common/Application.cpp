#include "Application.h"
#include "SDL.h"
#include "SDL_mixer.h"
namespace tggd::common
{
	Application* Application::s_application = nullptr;

	Application::Application(int width, int height, const std::string& title)
		: window(nullptr)
		, renderer(nullptr)
		, windowWidth(width)
		, windowHeight(height)
		, windowTitle(title)
	{
		if (!s_application)
		{
			s_application = this;
		}
	}

	void Application::Start()
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		Mix_Init(MIX_INIT_OGG);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		SDL_CreateWindowAndRenderer(
			s_application->windowWidth,
			s_application->windowHeight,
			0,
			&s_application->window,
			&s_application->renderer);
		SDL_SetWindowTitle(s_application->window, s_application->windowTitle.c_str());
		s_application->Start();
	}

	void Application::Pump()
	{
		int oldCounter = SDL_GetTicks();
		int frameCounter;
		SDL_Event evt;
		for (;;)
		{
			frameCounter = SDL_GetTicks();
			s_application->Update(frameCounter - oldCounter);
			oldCounter = frameCounter;
			s_application->Draw();
			SDL_RenderPresent(s_application->renderer);
			if (SDL_PollEvent(&evt))
			{
				if (!s_application->OnEvent(evt))
				{
					break;
				}
			}
		}

	}

	void Application::Finish()
	{
		s_application->Finish();
		if (s_application->renderer)
		{
			SDL_DestroyRenderer(s_application->renderer);
			s_application->renderer = nullptr;
		}
		if (s_application->window)
		{
			SDL_DestroyWindow(s_application->window);
			s_application->window = nullptr;
		}
		Mix_CloseAudio();
		Mix_Quit();
		SDL_Quit();
	}


	int Application::Run(const std::vector<std::string>& arguments)
	{
		if (s_application)
		{
			Start();
			Pump();
			Finish();
		}
		return 0;
	}
}
