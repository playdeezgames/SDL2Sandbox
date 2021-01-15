#pragma once
#include "..\Common\Application.h"
#include "..\Managers\RomFontManager.h"
class BaseRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	const RomFontManager& romFontManager;
protected:
	SDL_Renderer* GetMainRenderer() const;
	const RomFontManager& GetRomFont() const;
public:
	BaseRenderer(SDL_Renderer*, const RomFontManager&);
};

