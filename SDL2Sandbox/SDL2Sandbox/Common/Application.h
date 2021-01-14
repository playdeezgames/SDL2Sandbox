#pragma once
#include <SDL.h>
#include <string>
#include <vector>
namespace tggd::common
{
	class Thingie
	{
	protected:
		virtual void Start() = 0;
		virtual void Finish() = 0;
	};
	class Renderer
	{
	protected:
		virtual SDL_Renderer* GetMainRenderer() const = 0;
	public:
		virtual void Draw() = 0;
	};
	class Updater
	{
	protected:
		virtual void Update(int) = 0;
	};
	class EventHandler
	{
	public:
		virtual bool OnEvent(const SDL_Event&) = 0;
	};
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


