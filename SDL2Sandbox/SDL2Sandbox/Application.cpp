#include "Application.h"
#include "SDL.h"

int Application::Run(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);
	SDL_Event evt;
	for (;;)
	{
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		SDL_WaitEvent(&evt);
		if (evt.type == SDL_QUIT)
		{
			break;
		}
	}
	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
	return 0;
}
