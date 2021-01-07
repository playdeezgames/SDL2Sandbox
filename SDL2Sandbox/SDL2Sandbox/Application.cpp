#include "Application.h"
#include "SDL.h"

Application* Application::s_application = nullptr;

Application::Application()
	: window(nullptr)
	, renderer(nullptr)
{
	if (!s_application)
	{
		s_application = this;
	}
}

int Application::Run(const std::vector<std::string>& arguments)
{
	if (s_application)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_CreateWindowAndRenderer(640, 480, 0, &s_application->window, &s_application->renderer);
		s_application->Start();
		SDL_Event evt;
		for (;;)
		{
			s_application->Update();
			SDL_RenderClear(s_application->renderer);
			s_application->Draw();
			SDL_RenderPresent(s_application->renderer);
			SDL_WaitEvent(&evt);
			if (!s_application->OnEvent(evt))
			{
				break;
			}
		}
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
		SDL_Quit();
		return 0;
	}
}
