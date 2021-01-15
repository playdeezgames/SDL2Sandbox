#pragma once
#include "BaseRenderer.h"
#include "..\Game\OptionsState.h"
class OptionsRenderer : public BaseRenderer
{
private:
	const OptionsState& state;
	void RenderItem(int, const std::string&, const OptionsState&);
public:
	OptionsRenderer(SDL_Renderer*, const RomFontManager&, const OptionsState&);
	void Draw();
};

