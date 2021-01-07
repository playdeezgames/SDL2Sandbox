#include "SandboxApplication.h"

SandboxApplication::SandboxApplication()
	: Application(640, 480)
{

}

void SandboxApplication::Start()
{

}

void SandboxApplication::Finish()
{

}

bool SandboxApplication::OnEvent(const SDL_Event& evt)
{
	return evt.type != SDL_QUIT;
}

void SandboxApplication::Update()
{

}

void SandboxApplication::Draw()
{

}

SandboxApplication SandboxApplication::sandboxApplication;

