#pragma once
#include "..\Common\Application.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\RomFontManager.h"
#include "..\Game\GameData.h"
class GameOverRenderer: public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	const tggd::common::SoundManager& soundManager;
	const RomFontManager& romFontManager;
	const GameData& gameData;
protected:
	SDL_Renderer* GetMainRenderer() const;
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

