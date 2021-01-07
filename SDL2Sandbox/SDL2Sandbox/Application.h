#pragma once
#include "SDL.h"
#include <string>
#include <vector>
class Application
{
private:
	static Application* s_application;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int windowWidth;
	int windowHeight;
	int frameMilliseconds;
protected:
	SDL_Renderer* GetMainRenderer() const { return renderer; }
	virtual void Start() = 0;
	virtual void Finish() = 0;
	virtual bool OnEvent(const SDL_Event&) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	Application(int, int, int);
	static int Run(const std::vector<std::string>&);
};

