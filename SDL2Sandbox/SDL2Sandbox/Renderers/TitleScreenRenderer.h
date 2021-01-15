#pragma once
#include "..\Common\Application.h"
#include "..\Common\SoundManager.h"
#include "..\RomFontManager.h"
#include "..\Game\GameData.h"
class TitleScreenRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
	const tggd::common::SoundManager& soundManager;
	const RomFontManager& romFontManager;
	const GameData& gameData;
	void DrawMenuItem(int, const std::string&, const MainMenuItem&) const;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	TitleScreenRenderer
	(
		SDL_Renderer*,
		const tggd::common::SoundManager&,
		const RomFontManager&,
		const GameData&
	);
	void Draw();
};

