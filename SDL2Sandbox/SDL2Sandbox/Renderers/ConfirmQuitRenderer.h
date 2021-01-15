#pragma once
#include "BaseRenderer.h"
class ConfirmQuitRenderer : public BaseRenderer
{
private:
	const bool& confirm;
public:
	ConfirmQuitRenderer(SDL_Renderer*, const RomFontManager&, const bool&);
	void Draw();
};

