#include "SandboxApplication.h"
#include "SDL_image.h"
typedef struct
{
	bool muted;
} GameOptions;

SandboxApplication SandboxApplication::sandboxApplication;

SandboxApplication::SandboxApplication()
	: Application(GameConstants::WINDOW_WIDTH, GameConstants::WINDOW_HEIGHT, GameConstants::WINDOW_TITLE)
	, blocks(Constants::Board::ROWS)
	, counter(GameConstants::INITIAL_COUNTER)
	, direction(GameConstants::DIRECTION_RIGHT)
	, gameOver(GameConstants::INITIAL_GAME_OVER)
	, turnSound(nullptr)
	, deathSound(nullptr)
	, romfontTexture(nullptr)
	, runLength(GameConstants::INITIAL_RUN_LENGTH)
	, score(GameConstants::INITIAL_SCORE)
	, muted(GameConstants::INITIAL_MUTED)
	, romfontSrcRects()
	, dead(GameConstants::INITIAL_DEAD)
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
	for (int index = 0; index < GameConstants::ROMFONT_CELL_COUNT; ++index)
	{
		int column = index % GameConstants::ROMFONT_COLUMNS;
		int row = index / GameConstants::ROMFONT_COLUMNS;
		romfontSrcRects[index].x = column * GameConstants::ROMFONT_CELL_WIDTH;
		romfontSrcRects[index].y = row * GameConstants::ROMFONT_CELL_HEIGHT;
		romfontSrcRects[index].w = GameConstants::ROMFONT_CELL_WIDTH;
		romfontSrcRects[index].h = GameConstants::ROMFONT_CELL_HEIGHT;
	}

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

bool SandboxApplication::HandleInPlayKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_LEFT)
	{
		SetNextDirection(GameConstants::DIRECTION_LEFT);
	}
	else if (sym == SDLK_RIGHT)
	{
		SetNextDirection(GameConstants::DIRECTION_RIGHT);
	}
	return true;
}

bool SandboxApplication::HandleGameOverKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE)
	{
		RestartGame();
	}
	else if (sym == SDLK_m)
	{
		muted = !muted;
		SaveOptions();
	}
	return true;
}


bool SandboxApplication::HandleKeyDown(SDL_Keycode sym)
{
	if (!gameOver)
	{
		return HandleInPlayKeyDown(sym);
	}
	else
	{
		return HandleGameOverKeyDown(sym);
	}
}

bool SandboxApplication::OnEvent(const SDL_Event& evt)
{
	switch (evt.type)
	{
	case SDL_QUIT:
		return false;
	case SDL_KEYDOWN:
		return HandleKeyDown(evt.key.keysym.sym);
	default:
		return true;
	}
}

void SandboxApplication::UpdateTail()
{
	for (size_t row = 0; row < tail.size() - 1; ++row)
	{
		tail[row] = tail[row + 1];
	}
	tail[tail.size() - 1] = tail[tail.size() - 1] + direction;
}

void SandboxApplication::UpdateBlocks()
{
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
}

void SandboxApplication::CheckForGameOver()
{
	gameOver =
		blocks[tail.size() - 1] == tail[tail.size() - 1] ||
		tail[tail.size() - 1] < GameConstants::BLOCK_MINIMUM_RANDOM_COLUMN ||
		tail[tail.size() - 1] > GameConstants::BLOCK_MAXIMUM_RANDOM_COLUMN;

	if (gameOver)
	{
		dead = true;
		PlaySound(deathSound);
	}
	else
	{
		runLength++;
	}
}

void SandboxApplication::UpdateBoard()
{
	if (!gameOver)
	{
		UpdateTail();
		UpdateBlocks();
		CheckForGameOver();
	}
}

void SandboxApplication::Update(int milliseconds)
{
	counter += milliseconds;
	while (counter > GameConstants::FRAME_MILLISECONDS)
	{
		UpdateBoard();
		counter -= GameConstants::FRAME_MILLISECONDS;
	}
}

void SandboxApplication::DrawBackground()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());
}

void SandboxApplication::DrawTail()
{
	for (int row = 0; row < tail.size() - 1; ++row)
	{
		DrawCharacter(tail[row], row, '*', GameConstants::BROWN);
	}
	if (dead)
	{
		DrawCharacter(tail[(int)tail.size() - 1], (int)tail.size() - 1, '\x0F', GameConstants::RED);
	}
	else
	{
		DrawCharacter(tail[(int)tail.size() - 1], (int)tail.size() - 1, '\x02', GameConstants::WHITE);
	}
}

void SandboxApplication::PlotCellRect(SDL_Rect& rc, int column, int row)
{
	rc.x = column * Constants::Cell::WIDTH;
	rc.y = row * Constants::Cell::HEIGHT;
	rc.w = Constants::Cell::WIDTH;
	rc.h = Constants::Cell::HEIGHT;
}

void SandboxApplication::DrawBlocks()
{
	for (int row = 0; row < blocks.size(); ++row)
	{
		DrawCharacter(blocks[row], row, 0xdb, GameConstants::WHITE);
	}
}

void SandboxApplication::DrawWalls()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 255, 255);
	SDL_Rect rc = { GameConstants::DEFAULT_X,GameConstants::DEFAULT_Y,Constants::Cell::WIDTH, GameConstants::WINDOW_HEIGHT };
	SDL_RenderFillRect(GetMainRenderer(), &rc);
	rc.x = GameConstants::WINDOW_WIDTH - Constants::Cell::WIDTH;
	SDL_RenderFillRect(GetMainRenderer(), &rc);
}

void SandboxApplication::DrawScore()
{
	SDL_SetTextureColorMod(romfontTexture, 0, 255, 0);
	SDL_Rect rc =
	{
		Constants::Cell::WIDTH,
		GameConstants::DEFAULT_Y,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	int digits = 1;//there is always at least one score digit
	int temp = score;
	while (temp >= GameConstants::SCORE_RADIX)
	{
		digits++;
		temp /= GameConstants::SCORE_RADIX;
		rc.x += Constants::Cell::WIDTH;
	}
	temp = score;
	while (digits)
	{
		int digit = temp % GameConstants::SCORE_RADIX;
		temp /= GameConstants::SCORE_RADIX;
		digits--;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &(romfontSrcRects['0' + digit]), &rc);
		rc.x -= Constants::Cell::WIDTH;
	}
}

void SandboxApplication::DrawMuteHint()
{
	if (muted)
	{
		DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, GameConstants::UNMUTE_HINT_TEXT, GameConstants::DARK_MAGENTA);
	}
	else
	{
		DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, GameConstants::MUTE_HINT_TEXT, GameConstants::DARK_MAGENTA);
	}
}

void SandboxApplication::DrawStartHint()
{
	DrawCenteredText(GameConstants::START_MESSAGE_ROW, GameConstants::START_HINT_TEXT, GameConstants::DARK_MAGENTA);
}

void SandboxApplication::DrawHints()
{
	if (gameOver)
	{
		DrawMuteHint();
		DrawStartHint();
	}
}

void SandboxApplication::Draw()
{
	DrawBackground();
	DrawBlocks();
	DrawWalls();
	DrawTail();
	DrawScore();
	DrawHints();
}


void SandboxApplication::ResetGame()
{
	blocks.clear();
	while (blocks.size() < Constants::Board::ROWS)
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
	dead = GameConstants::INITIAL_DEAD;
}

void SandboxApplication::RestartGame()
{
	ResetGame();
	gameOver = false;
}

void SandboxApplication::DrawCenteredText(int row, const std::string& text, const SDL_Color& color)
{
	//you center things by dividing by 2
	DrawText((Constants::Board::COLUMNS - (int)text.size()) / 2, row, text, color);
}

void SandboxApplication::DrawCharacter(int column, int row, char character, const SDL_Color& color)
{
	SDL_SetTextureColorMod(romfontTexture, color.r, color.g, color.b);
	SDL_Rect rcDst =
	{
		column * Constants::Cell::WIDTH,
		row * Constants::Cell::HEIGHT,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	SDL_RenderCopy(GetMainRenderer(), romfontTexture, &(romfontSrcRects[(unsigned char)character]), &rcDst);
}

void SandboxApplication::DrawText(int column, int row, const std::string& text, const SDL_Color& color)
{
	for (auto ch : text)
	{
		DrawCharacter(column, row, ch, color);
		column++;
	}
}
void SandboxApplication::PlaySound(Mix_Chunk* chunk)
{
	if (!muted)
	{
		Mix_PlayChannel(GameConstants::ANY_CHANNEL, chunk, GameConstants::NO_LOOPS);
	}
}