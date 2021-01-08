#include "SandboxApplication.h"
#include "SDL_image.h"
SandboxApplication SandboxApplication::sandboxApplication;

SandboxApplication::SandboxApplication()
	: Application(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT, GameConstants::WINDOW_TITLE)
	, blocks(GameConstants::BOARD_ROWS)
	, counter(0)
	, direction(1)
	, gameOver(true)
	, turnSound(nullptr)
	, deathSound(nullptr)
	, romfontTexture(nullptr)
	, runLength(0)
	, score(0)
{

}

void SandboxApplication::Start()
{
	IMG_Init(IMG_INIT_PNG);
	romfontTexture = IMG_LoadTexture(GetMainRenderer(), "romfont8x8.png");
	turnSound = Mix_LoadWAV("jl2017turn.wav");
	deathSound = Mix_LoadWAV("jl2017death.wav");
	ResetGame();
}

void SandboxApplication::Finish()
{
	Mix_FreeChunk(turnSound);
	Mix_FreeChunk(deathSound);
	SDL_DestroyTexture(romfontTexture);
	IMG_Quit();
}

bool SandboxApplication::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		if (!gameOver)
		{
			if (evt.key.keysym.sym == SDLK_LEFT && direction != -1)
			{
				score += (runLength * (runLength + 1)) / 2;
				runLength = 0;
				Mix_PlayChannel(-1, turnSound, 0);
				direction = -1;
			}
			else if (evt.key.keysym.sym == SDLK_RIGHT && direction != 1)
			{
				score += (runLength * (runLength + 1)) / 2;
				runLength = 0;
				Mix_PlayChannel(-1, turnSound, 0);
				direction = 1;
			}
		}
		else
		{
			if (evt.key.keysym.sym == SDLK_SPACE)
			{
				RestartGame();
			}
		}
		return true;
	default:
		return true;
	}
}

void SandboxApplication::Update(int milliseconds)
{
	counter += milliseconds;
	while (counter > GameConstants::FRAME_MILLISECONDS)
	{
		if (!gameOver)
		{
			for (size_t row = 0; row < tail.size() - 1; ++row)
			{
				tail[row] = tail[row + 1];
			}
			tail[tail.size() - 1] = tail[tail.size() - 1] + direction;

			for (size_t row = 0; row < blocks.size() - 1; ++row)
			{
				blocks[row] = blocks[(size_t)(row + 1)];
			}
			blocks[blocks.size() - 1] =
				rand() %
				(GameConstants::BLOCK_MAXIMUM_RANDOM_COLUMN -
					GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN +
					1) +
				GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN;

			gameOver =
				blocks[tail.size() - 1] == tail[tail.size() - 1] ||
				tail[tail.size() - 1] < GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN ||
				tail[tail.size() - 1] > GameConstants::BLOCK_MAXIMUM_RANDOM_COLUMN;

			if (gameOver)
			{
				Mix_PlayChannel(-1, deathSound, 0);
			}
			else
			{
				runLength++;
			}
		}

		counter -= GameConstants::FRAME_MILLISECONDS;
	}
}

void SandboxApplication::Draw()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());

	SDL_Rect rc = { 0,0,GameConstants::CELL_WIDTH, GameConstants::CELL_HEIGHT };
	for (int row = 0; row < tail.size(); ++row)
	{
		SDL_SetRenderDrawColor(GetMainRenderer(), 255, (row < tail.size() - 1) ? (255) : (0), 0, 255);
		rc.x = tail[row] * GameConstants::CELL_WIDTH;
		rc.y = row * GameConstants::CELL_HEIGHT;
		SDL_RenderFillRect(GetMainRenderer(), &rc);

	}

	SDL_SetRenderDrawColor(GetMainRenderer(), 255, 255, 255, 255);
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

	SDL_SetTextureColorMod(romfontTexture, 0, 255, 0);
	rc.x = GameConstants::CELL_WIDTH;
	rc.y = 0;
	rc.w = GameConstants::CELL_WIDTH;
	rc.h = GameConstants::CELL_HEIGHT;
	int digits = 1;
	int temp = score;
	while (temp > 9)
	{
		digits++;
		temp /= 10;
		rc.x += GameConstants::CELL_WIDTH;
	}
	SDL_Rect rcSrc = { 0, GameConstants::CELL_HEIGHT * 3, GameConstants::CELL_WIDTH, GameConstants::CELL_HEIGHT };
	temp = score;
	while (digits > 0)
	{
		int digit = temp % 10;
		temp /= 10;
		digits--;
		rcSrc.x = digit * GameConstants::CELL_WIDTH;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &rcSrc, &rc);
		rc.x -= GameConstants::CELL_WIDTH;
	}

	if (gameOver)
	{
		DrawText((GameConstants::BOARD_COLUMNS - 24)/2, GameConstants::BOARD_ROWS - 1, "Press <SPACE> to Start!!", 128, 0, 128);
	}
}


void SandboxApplication::ResetGame()
{
	blocks.clear();
	while (blocks.size() < GameConstants::BOARD_ROWS)
	{
		blocks.push_back(GameConstants::BLOCK_INITIAL_COLUMN);
	}

	tail.clear();
	while (tail.size() < GameConstants::TAIL_LENGTH)
	{
		tail.push_back(GameConstants::TAIL_INITIAL_COLUMN);
	}

	direction = 1;
	score = 0;
	runLength = 0;
}

void SandboxApplication::RestartGame()
{
	ResetGame();
	gameOver = false;
}

void SandboxApplication::DrawText(int column, int row, const std::string& text, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(romfontTexture, r, g, b);
	SDL_Rect rcSrc = { 0, 0, GameConstants::CELL_WIDTH, GameConstants::CELL_HEIGHT };
	SDL_Rect rcDst = { column * GameConstants::CELL_WIDTH, row * GameConstants::CELL_HEIGHT, GameConstants::CELL_WIDTH, GameConstants::CELL_HEIGHT };
	for (auto ch : text)
	{
		rcSrc.x = (ch % 16) * GameConstants::CELL_WIDTH;
		rcSrc.y = (ch / 16) * GameConstants::CELL_HEIGHT;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &rcSrc, &rcDst);
		rcDst.x += GameConstants::CELL_WIDTH;
	}
}