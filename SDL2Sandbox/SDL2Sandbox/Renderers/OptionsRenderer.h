#pragma once
#include "BaseRenderer.h"
#include "..\Game\OptionsState.h"
#include "..\Common\SoundManager.h"
class OptionsRenderer : public BaseRenderer
{
private:
	const OptionsState& state;
	tggd::common::SoundManager& soundManager;
	void RenderItem(int, const std::string&, const OptionsState&);
public:
	OptionsRenderer(SDL_Renderer*, const RomFontManager&, const OptionsState&, tggd::common::SoundManager&);
	void Draw();
};

