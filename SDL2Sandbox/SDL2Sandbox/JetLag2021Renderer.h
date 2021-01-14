#pragma once
#include <SDL.h>
#include "Constants.h"
#include "GameData.h"
#include "..\..\..\CommonCpp\SoundManager.h"
#include "..\..\..\CommonCpp\Application.h"
#include "RomFontManager.h"
class JetLag2021Renderer : public tggd::common::Renderer
{
private:
	const GameData& gameData;
	const tggd::common::SoundManager& soundManager;
	const RomFontManager& romFontManager;
	SDL_Renderer* renderer;
	void DrawBackground();
	void DrawTail();
	void DrawBlocks();
	void DrawPickUps();
	void DrawWalls();
	void DrawScore();
	void DrawBombs();
	void DrawStatusBar();
	static void PlotCellRect(SDL_Rect&, int, int);
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	JetLag2021Renderer(const GameData&, const tggd::common::SoundManager&, const RomFontManager&);
	void Start(SDL_Renderer*);
	void Finish();
	void Draw();
};

