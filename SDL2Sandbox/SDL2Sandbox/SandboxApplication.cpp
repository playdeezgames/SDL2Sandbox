#include "SandboxApplication.h"

SandboxApplication::SandboxApplication()
	: Application(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT, GameConstants::FRAME_MILLISECONDS)
	, blocks(GameConstants::BOARD_ROWS)
{

}

void SandboxApplication::Start()
{
	blocks.clear();
	while (blocks.size() < GameConstants::BOARD_ROWS)
	{
		blocks.push_back(GameConstants::BLOCK_INITIAL_COLUMN);
	}
}

void SandboxApplication::Finish()
{

}

bool SandboxApplication::OnEvent(const SDL_Event& evt)
{
	return evt.type != SDL_QUIT;
}

void SandboxApplication::Update()
{
	for (auto row = 0; row < blocks.size() - 1; ++row)
	{
		blocks[row] = blocks[row + 1];
	}
	blocks[blocks.size() - 1] = rand() % (GameConstants::BLOCK_MAXIMUM_RANDOM_COLUMN - GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN + 1) + GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN;
}

void SandboxApplication::Draw()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());

	SDL_SetRenderDrawColor(GetMainRenderer(), 255, 255, 255, 255);
	SDL_Rect rc = { 0,0,GameConstants::CELL_WIDTH, GameConstants::CELL_HEIGHT };
	for (int row = 0; row < blocks.size(); ++row)
	{
		rc.x = blocks[row] * GameConstants::CELL_WIDTH;
		rc.y = row * GameConstants::CELL_HEIGHT;
		SDL_RenderFillRect(GetMainRenderer(), &rc);
	}
}

SandboxApplication SandboxApplication::sandboxApplication;

