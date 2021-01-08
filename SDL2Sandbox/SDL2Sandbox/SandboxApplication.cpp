#include "SandboxApplication.h"
#include "SDL_image.h"
typedef struct
{
	bool muted;
} GameOptions;

SandboxApplication SandboxApplication::sandboxApplication;

SandboxApplication::SandboxApplication()
	: Application(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT, GameConstants::WINDOW_TITLE)
	, blocks(GameConstants::BOARD_ROWS)
	, counter(GameConstants::INITIAL_COUNTER)
	, direction(GameConstants::DIRECTION_RIGHT)
	, gameOver(GameConstants::INITIAL_GAME_OVER)
	, turnSound(nullptr)
	, deathSound(nullptr)
	, romfontTexture(nullptr)
	, runLength(GameConstants::INITIAL_RUN_LENGTH)
	, score(GameConstants::INITIAL_SCORE)
	, muted(GameConstants::INITIAL_MUTED)
{
}

void SandboxApplication::SaveOptions()
{
	remove(GameConstants::OPTIONS_FILE_NAME.c_str());
	FILE* f = nullptr;
	fopen_s(&f, GameConstants::OPTIONS_FILE_NAME.c_str(), GameConstants::OPTIONS_WRITE_MODE.c_str());
	if (f)
	{
		GameOptions options = { 0 };
		options.muted = muted;
		fwrite(&options, sizeof(GameOptions), GameConstants::OPTIONS_RECORD_COUNT, f);
		fclose(f);
	}
}

void SandboxApplication::LoadOptions()
{
	FILE* f = nullptr;
	fopen_s(&f, GameConstants::OPTIONS_FILE_NAME.c_str(), GameConstants::OPTIONS_READ_MODE.c_str());
	if (f)
	{
		GameOptions options;
		fseek(f, 0, SEEK_END);//seek to end of file to determine position
		if (ftell(f) == sizeof(GameOptions))
		{
			fseek(f, 0, SEEK_SET);//reset to start of file for reading
			fread(&options, sizeof(GameOptions), GameConstants::OPTIONS_RECORD_COUNT, f);
			muted = options.muted;
		}
		fclose(f);
	}
}

void SandboxApplication::Start()
{
	LoadOptions();
	IMG_Init(IMG_INIT_PNG);
	romfontTexture = IMG_LoadTexture(GetMainRenderer(), GameConstants::ROMFONT_IMAGE_FILE_NAME.c_str());
	turnSound = Mix_LoadWAV(GameConstants::TURN_SOUND_FILE_NAME.c_str());
	deathSound = Mix_LoadWAV(GameConstants::DEATH_SOUND_FILE_NAME.c_str());
	ResetGame();
}

void SandboxApplication::Finish()
{
	Mix_FreeChunk(turnSound);
	Mix_FreeChunk(deathSound);
	SDL_DestroyTexture(romfontTexture);
	IMG_Quit();
}

static int CalculateScoreFromRunLength(int runLength)
{
	//"triangular number"
	//incentivizes risk by keeping going in a particular direction without turning
	return (runLength * (runLength + 1)) / 2;
}

void SandboxApplication::SetNextDirection(int nextDirection)
{
	if (nextDirection != direction)
	{
		score += CalculateScoreFromRunLength(runLength);
		runLength = GameConstants::INITIAL_RUN_LENGTH;
		PlaySound(turnSound);
		direction = nextDirection;
	}
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
			if (evt.key.keysym.sym == SDLK_LEFT)
			{
				SetNextDirection(GameConstants::DIRECTION_LEFT);
			}
			else if (evt.key.keysym.sym == SDLK_RIGHT)
			{
				SetNextDirection(GameConstants::DIRECTION_RIGHT);
			}
		}
		else
		{
			if (evt.key.keysym.sym == SDLK_SPACE)
			{
				RestartGame();
			}
			else if (evt.key.keysym.sym == SDLK_m)
			{
				muted = !muted;
				SaveOptions();
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
				PlaySound(deathSound);
			}
			else
			{
				runLength++;
			}
		}

		counter -= GameConstants::FRAME_MILLISECONDS;
	}
}

void SandboxApplication::DrawBackground()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());
}

void SandboxApplication::Draw()
{
	DrawBackground();

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
	int digits = 1;//there is always at least one score digit
	int temp = score;
	while (temp >= GameConstants::SCORE_RADIX)
	{
		digits++;
		temp /= GameConstants::SCORE_RADIX;
		rc.x += GameConstants::CELL_WIDTH;
	}
	SDL_Rect rcSrc = 
		{ 
			GameConstants::DEFAULT_X, 
			GameConstants::CELL_HEIGHT * GameConstants::ROMFONT_DIGITS_ROW, 
			GameConstants::CELL_WIDTH, 
			GameConstants::CELL_HEIGHT 
		};
	temp = score;
	while (digits)
	{
		int digit = temp % GameConstants::SCORE_RADIX;
		temp /= GameConstants::SCORE_RADIX;
		digits--;
		rcSrc.x = digit * GameConstants::CELL_WIDTH;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &rcSrc, &rc);
		rc.x -= GameConstants::CELL_WIDTH;
	}

	if (gameOver)
	{
		if (muted)
		{
			DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, "<M> to unmute", 128, 0, 128);
		}
		else
		{
			DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, "<M> to mute", 128, 0, 128);
		}
		DrawCenteredText(GameConstants::START_MESSAGE_ROW, "Press <SPACE> to Start!!", 128, 0, 128);
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

	direction = GameConstants::DIRECTION_RIGHT;
	score = GameConstants::INITIAL_SCORE;
	runLength = GameConstants::INITIAL_RUN_LENGTH;
}

void SandboxApplication::RestartGame()
{
	ResetGame();
	gameOver = false;
}

void SandboxApplication::DrawCenteredText(int row, const std::string& text, Uint8 r, Uint8 g, Uint8 b)
{
	DrawText((GameConstants::BOARD_COLUMNS - (int)text.size()) / 2, row, text, r, g, b);
}

void SandboxApplication::DrawText(int column, int row, const std::string& text, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(romfontTexture, r, g, b);
	SDL_Rect rcSrc = 
		{ 
			GameConstants::DEFAULT_X, 
			GameConstants::DEFAULT_Y, 
			GameConstants::CELL_WIDTH, 
			GameConstants::CELL_HEIGHT 
		};
	SDL_Rect rcDst = 
		{ 
			column * GameConstants::CELL_WIDTH, 
			row * GameConstants::CELL_HEIGHT, 
			GameConstants::CELL_WIDTH, 
			GameConstants::CELL_HEIGHT 
		};
	for (auto ch : text)
	{
		rcSrc.x = (ch % GameConstants::ROMFONT_COLUMNS) * GameConstants::CELL_WIDTH;
		rcSrc.y = (ch / GameConstants::ROMFONT_COLUMNS) * GameConstants::CELL_HEIGHT;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &rcSrc, &rcDst);
		rcDst.x += GameConstants::CELL_WIDTH;
	}
}
void SandboxApplication::PlaySound(Mix_Chunk* chunk)
{
	if (!muted)
	{
		Mix_PlayChannel(GameConstants::ANY_CHANNEL, chunk, GameConstants::NO_LOOPS);
	}
}