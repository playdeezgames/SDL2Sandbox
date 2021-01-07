#pragma once
#include "Application.h"
#include "GameConstants.h"
#include <vector>
class SandboxApplication: public Application
{
private:
	static SandboxApplication sandboxApplication;
	std::vector<int> blocks;
protected:
	void Start();
	void Finish();
	bool OnEvent(const SDL_Event&);
	void Update(int);
	void Draw();
public:
	SandboxApplication();
};

