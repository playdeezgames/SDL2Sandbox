#include "SandboxApplication.h"
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

