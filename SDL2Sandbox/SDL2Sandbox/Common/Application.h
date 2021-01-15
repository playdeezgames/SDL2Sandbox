#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Thingie.h"
#include "Renderer.h"
#include "Updater.h"
#include "EventHandler.h"
namespace tggd::common
{
	class Application : public Thingie, public Renderer, public Updater, public EventHandler
	{
	private:
		static Application* s_application;
		SDL_Window* window;
		SDL_Renderer* renderer;
		int windowWidth;
		int windowHeight;
		std::string windowTitle;
	protected:
		SDL_Renderer* GetMainRenderer() const { return renderer; }
	public:
		Application(int, int, const std::string&);
		static int Run(const std::vector<std::string>&);
	};
}


