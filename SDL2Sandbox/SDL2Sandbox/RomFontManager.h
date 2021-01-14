#pragma once
#include <SDL.h>
#include "Constants.h"
class RomFontManager
{
private:
	SDL_Texture* romfontTexture;
	SDL_Rect romfontSrcRects[Constants::RomFont::CELL_COUNT];
public:
	void Start(SDL_Renderer*);
	void Finish();
	void DrawCharacter(SDL_Renderer*, int, int, char, const SDL_Color&) const;
	void DrawText(SDL_Renderer*, int, int, const std::string&, const SDL_Color&) const;
	void DrawCenteredText(SDL_Renderer*, int, const std::string&, const SDL_Color&) const;

};

