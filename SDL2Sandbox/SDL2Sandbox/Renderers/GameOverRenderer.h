#pragma once
#include "BaseRenderer.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\RomFontManager.h"
#include "..\Game\GameData.h"
class GameOverRenderer: public BaseRenderer
{
protected:
	void DrawHints();
	void DrawMenuHint();
	void DrawStartHint();
public:
	GameOverRenderer
		(
			SDL_Renderer*, 
			const RomFontManager&
		);
	void Draw();
};

