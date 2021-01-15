#pragma once
#include "BaseRenderer.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\RomFontManager.h"
#include "..\Game\GameData.h"
class GameOverRenderer: public BaseRenderer
{
private:
	const tggd::common::SoundManager& soundManager;
	const RomFontManager& romFontManager;
	const GameData& gameData;
protected:
	void DrawHints();
	void DrawMuteHint();
	void DrawStartHint();
public:
	GameOverRenderer
		(
			SDL_Renderer*, 
			const tggd::common::SoundManager&, 
			const RomFontManager&, 
			const GameData&
		);
	void Draw();
};

