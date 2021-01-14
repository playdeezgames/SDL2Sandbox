#pragma once
#include "..\..\..\CommonCpp\Application.h"
class TitleScreenRenderer : public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	TitleScreenRenderer
	(
		SDL_Renderer*
	);
	void Draw();
};

