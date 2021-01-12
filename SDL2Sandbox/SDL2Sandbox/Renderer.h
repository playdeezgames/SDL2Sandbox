#pragma once
#include <SDL.h>
#include "Constants.h"
#include "GameData.h"
#include "..\..\..\CommonCpp\SoundManager.h"
class Renderer
{
private:
	const GameData& gameData;
	const tggd::common::SoundManager& soundManager;
	SDL_Renderer* renderer;
	SDL_Texture* romfontTexture;
	SDL_Rect romfontSrcRects[Constants::RomFont::CELL_COUNT];
	void DrawCharacter(int, int, char, const SDL_Color&);
	void DrawText(int, int, const std::string&, const SDL_Color&);
	void DrawCenteredText(int, const std::string&, const SDL_Color&);
	void DrawBackground();
	void DrawTail();
	void DrawBlocks();
	void DrawPickUps();
	void DrawWalls();
	void DrawScore();
	void DrawBombs();
	void DrawHints();
	void DrawMuteHint();
	void DrawStartHint();
	static void PlotCellRect(SDL_Rect&, int, int);
public:
	Renderer(const GameData&, const tggd::common::SoundManager&);
	void Start(SDL_Renderer*);
	void Finish();
	void Draw();
};

