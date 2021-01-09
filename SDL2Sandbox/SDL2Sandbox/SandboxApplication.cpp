#include "SandboxApplication.h"
#include "SDL_image.h"
typedef struct
{
	bool muted;
} GameOptions;

SandboxApplication SandboxApplication::sandboxApplication;

SandboxApplication::SandboxApplication()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, blocks(Constants::Board::ROWS)
	, counter(Constants::Game::InitialValues::COUNTER)
	, direction(Constants::Game::Direction::RIGHT)
	, gameOver(Constants::Game::InitialValues::GAME_OVER)
	, turnSound(nullptr)
	, deathSound(nullptr)
	, romfontTexture(nullptr)
	, runLength(Constants::Game::InitialValues::RUN_LENGTH)
	, score(Constants::Game::InitialValues::SCORE)
	, muted(Constants::Game::InitialValues::MUTED)
	, romfontSrcRects()
	, dead(Constants::Game::InitialValues::DEAD)
{
}

void SandboxApplication::SaveOptions()
{
	remove(Constants::Options::FILE_NAME.c_str());
	FILE* f = nullptr;
	fopen_s(&f, Constants::Options::FILE_NAME.c_str(), Constants::Options::WRITE_MODE.c_str());
	if (f)
	{
		GameOptions options = { 0 };
		options.muted = muted;
		fwrite(&options, sizeof(GameOptions), Constants::Options::RECORD_COUNT, f);
		fclose(f);
	}
}

void SandboxApplication::LoadOptions()
{
	FILE* f = nullptr;
	fopen_s(&f, Constants::Options::FILE_NAME.c_str(), Constants::Options::READ_MODE.c_str());
	if (f)
	{
		GameOptions options;
		fseek(f, 0, SEEK_END);//seek to end of file to determine position
		if (ftell(f) == sizeof(GameOptions))
		{
			fseek(f, 0, SEEK_SET);//reset to start of file for reading
			fread(&options, sizeof(GameOptions), Constants::Options::RECORD_COUNT, f);
			muted = options.muted;
		}
		fclose(f);
	}
}

void SandboxApplication::Start()
{
	for (int index = 0; index < Constants::RomFont::CELL_COUNT; ++index)
	{
		int column = index % Constants::RomFont::COLUMNS;
		int row = index / Constants::RomFont::COLUMNS;
		romfontSrcRects[index].x = column * Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].y = row * Constants::RomFont::CELL_HEIGHT;
		romfontSrcRects[index].w = Constants::RomFont::CELL_WIDTH;
		romfontSrcRects[index].h = Constants::RomFont::CELL_HEIGHT;
	}

	LoadOptions();
	IMG_Init(IMG_INIT_PNG);
	romfontTexture = IMG_LoadTexture(GetMainRenderer(), Constants::RomFont::IMAGE_FILE_NAME.c_str());
	turnSound = Mix_LoadWAV(Constants::SoundFile::TURN.c_str());
	deathSound = Mix_LoadWAV(Constants::SoundFile::DEATH.c_str());
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
		runLength = Constants::Game::InitialValues::RUN_LENGTH;
		PlaySound(turnSound);
		direction = nextDirection;
	}
}

bool SandboxApplication::HandleInPlayKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_LEFT)
	{
		SetNextDirection(Constants::Game::Direction::LEFT);
	}
	else if (sym == SDLK_RIGHT)
	{
		SetNextDirection(Constants::Game::Direction::RIGHT);
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
		(Constants::Block::MAXIMUM_RANDOM_COLUMN -
			Constants::Block::MINIMUM_RANDOM_COLUMN +
			1) +
		Constants::Block::MINIMUM_RANDOM_COLUMN;
}

void SandboxApplication::CheckForGameOver()
{
	gameOver =
		blocks[tail.size() - 1] == tail[tail.size() - 1] ||
		tail[tail.size() - 1] < Constants::Block::MINIMUM_RANDOM_COLUMN ||
		tail[tail.size() - 1] > Constants::Block::MAXIMUM_RANDOM_COLUMN;

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
	while (counter > Constants::Game::FRAME_MILLISECONDS)
	{
		UpdateBoard();
		counter -= Constants::Game::FRAME_MILLISECONDS;
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
		DrawCharacter(tail[row], row, '*', Constants::Color::BROWN);
	}
	if (dead)
	{
		DrawCharacter(tail[(int)tail.size() - 1], (int)tail.size() - 1, '\x0F', Constants::Color::RED);
	}
	else
	{
		DrawCharacter(tail[(int)tail.size() - 1], (int)tail.size() - 1, '\x02', Constants::Color::WHITE);
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
		DrawCharacter(blocks[row], row, (char)0xdb, Constants::Color::WHITE);
	}
}

void SandboxApplication::DrawWalls()
{
	for (int row = 0; row < blocks.size(); ++row)
	{
		DrawCharacter(Constants::Board::LEFT_WALL, row, (char)0xdb, Constants::Color::BLUE);
		DrawCharacter(Constants::Board::RIGHT_WALL, row, (char)0xdb, Constants::Color::BLUE);
	}
}

void SandboxApplication::DrawScore()
{
	SDL_SetTextureColorMod(romfontTexture, 0, 255, 0);
	SDL_Rect rc =
	{
		Constants::Cell::WIDTH,
		Constants::Utility::DEFAULT_Y,
		Constants::Cell::WIDTH,
		Constants::Cell::HEIGHT
	};
	int digits = 1;//there is always at least one score digit
	int temp = score;
	while (temp >= Constants::Game::SCORE_RADIX)
	{
		digits++;
		temp /= Constants::Game::SCORE_RADIX;
		rc.x += Constants::Cell::WIDTH;
	}
	temp = score;
	while (digits)
	{
		int digit = temp % Constants::Game::SCORE_RADIX;
		temp /= Constants::Game::SCORE_RADIX;
		digits--;
		SDL_RenderCopy(GetMainRenderer(), romfontTexture, &(romfontSrcRects['0' + digit]), &rc);
		rc.x -= Constants::Cell::WIDTH;
	}
}

void SandboxApplication::DrawMuteHint()
{
	if (muted)
	{
		DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, GameConstants::UNMUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
	else
	{
		DrawCenteredText(GameConstants::MUTE_MESSAGE_ROW, GameConstants::MUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
}

void SandboxApplication::DrawStartHint()
{
	DrawCenteredText(GameConstants::START_MESSAGE_ROW, GameConstants::START_HINT_TEXT, Constants::Color::MAGENTA);
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
		blocks.push_back(Constants::Block::INITIAL_COLUMN);
	}

	tail.clear();
	while (tail.size() < Constants::Tail::LENGTH)
	{
		tail.push_back(Constants::Tail::INITIAL_COLUMN);
	}

	direction = Constants::Game::Direction::RIGHT;
	score = Constants::Game::InitialValues::SCORE;
	runLength = Constants::Game::InitialValues::RUN_LENGTH;
	dead = Constants::Game::InitialValues::DEAD;
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
		Mix_PlayChannel(Constants::Utility::ANY_CHANNEL, chunk, Constants::Utility::NO_LOOPS);
	}
}