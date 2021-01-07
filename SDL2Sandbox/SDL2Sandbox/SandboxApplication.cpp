#include "SandboxApplication.h"

SandboxApplication::SandboxApplication()
	: Application(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT)
	, blocks(GameConstants::BOARD_ROWS)
	, counter(0)
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

void SandboxApplication::Update(int milliseconds)
{
	counter += milliseconds;
	while (counter > GameConstants::FRAME_MILLISECONDS)
	{
		for (size_t row = 0; row < blocks.size() - 1; ++row)
		{
			blocks[row] = blocks[(size_t)(row + 1)];
		}
		blocks[blocks.size() - 1] = rand() % (GameConstants::BLOCK_MAXIMUM_RANDOM_COLUMN - GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN + 1) + GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN;
		counter -= GameConstants::FRAME_MILLISECONDS;
	}
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

	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 255, 255);
	rc.x = 0;
	rc.y = 0;
	rc.w = GameConstants::CELL_WIDTH;
	rc.h = GameConstants::WINDOW_HEIGHT;
	SDL_RenderFillRect(GetMainRenderer(), &rc);
	rc.x = GameConstants::WINDOW_WIDTH - GameConstants::CELL_WIDTH;
	SDL_RenderFillRect(GetMainRenderer(), &rc);
}

SandboxApplication SandboxApplication::sandboxApplication;

