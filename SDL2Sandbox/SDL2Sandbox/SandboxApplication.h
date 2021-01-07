#pragma once
#include "Application.h"
class SandboxApplication: public Application
{
private:
	static SandboxApplication sandboxApplication;
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update();
	void Draw();
public:
	SandboxApplication();
};

