#pragma once
#include "..\..\..\CommonCpp\Application.h"
class InPlayEventHandler : tggd::common::EventHandler
{
public:
	bool OnEvent(const SDL_Event&);
};

