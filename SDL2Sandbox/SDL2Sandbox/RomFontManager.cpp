#include "RomFontManager.h"
#include <SDL_image.h>
#include "Constants\Board.h"
void RomFontManager::Start(SDL_Renderer* renderer)
{
	for (int index = 0; index < Constants::RomFont::CELL_COUNT; ++index)
	{
		int column = index % Constants::RomFont::COLUMNS;
		int row = index / Constants::RomFont::COLUMNS;
		romfontSrcRects[index].x = column * Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].y = row * Constants::RomFont::CELL_HEIGHT;
		romfontSrcRects[index].w = Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].h = Constants::RomFont::CELL_HEIGHT;
	}
	romfontTexture = IMG_LoadTexture(renderer, Constants::RomFont::IMAGE_FILE_NAME.c_str());
}

void RomFontManager::Finish()
{
	if (romfontTexture)
	{
		SDL_DestroyTexture(romfontTexture);
		romfontTexture = nullptr;
	}
}

void RomFontManager::DrawCharacter(SDL_Renderer* renderer, int column, int row, char character, const SDL_Color& color) const
{
	SDL_SetTextureColorMod(romfontTexture, color.r, color.g, color.b);
	SDL_Rect rcDst =
	{
		column * Constants::Cell::WIDTH,
		row * Constants::Cell::HEIGHT,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	SDL_RenderCopy(renderer, romfontTexture, &(romfontSrcRects[(unsigned char)character]), &rcDst);
}

void RomFontManager::DrawCenteredText(SDL_Renderer* renderer, int row, const std::string& text, const SDL_Color& color) const
{
	//you center things by dividing by 2
	DrawText(renderer, (Constants::Board::COLUMNS - (int)text.size()) / 2, row, text, color);
}

void RomFontManager::DrawText(SDL_Renderer* renderer, int column, int row, const std::string& text, const SDL_Color& color) const
{
	for (auto ch : text)
	{
		DrawCharacter(renderer, column, row, ch, color);
		column++;
	}
}

