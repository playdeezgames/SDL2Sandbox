#pragma once
#include "BaseRenderer.h"
#include "..\Common\SoundManager.h"
#include "..\Managers\RomFontManager.h"
#include "..\Game\MainMenuItem.h"
class TitleScreenRenderer : public BaseRenderer
{
private:
	const tggd::common::SoundManager& soundManager;
	const MainMenuItem& mainMenuItem;
	void DrawMenuItem(int, const std::string&, const MainMenuItem&) const;
public:
	TitleScreenRenderer
	(
		SDL_Renderer*,
		const tggd::common::SoundManager&,
		const RomFontManager&,
		const MainMenuItem&
	);
	void Draw();
};

