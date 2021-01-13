#pragma once
#include "..\..\..\CommonCpp\Application.h"
class GameOverRenderer: public tggd::common::Renderer
{
private:
	SDL_Renderer* renderer;
protected:
	SDL_Renderer* GetMainRenderer() const;
public:
	GameOverRenderer(SDL_Renderer*);
	void Draw();
};

