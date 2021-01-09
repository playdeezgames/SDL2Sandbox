#include "JetLag2021Application.h"
#include "SDL_image.h"
typedef struct
{
	bool muted;
} GameOptions;

JetLag2021Application JetLag2021Application::sandboxApplication;

JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, blocks(Constants::Board::ROWS)
	, pickUps(Constants::Board::ROWS)
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

void JetLag2021Application::SaveOptions()
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

void JetLag2021Application::LoadOptions()
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

void JetLag2021Application::Start()
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
	chompSound = Mix_LoadWAV(Constants::SoundFile::CHOMP.c_str());
	ResetGame();
}

void JetLag2021Application::Finish()
{
	Mix_FreeChunk(turnSound);
	Mix_FreeChunk(deathSound);
	Mix_FreeChunk(chompSound);
	SDL_DestroyTexture(romfontTexture);
	IMG_Quit();
}

static int CalculateScoreFromRunLength(int runLength)
{
	//"triangular number"
	//incentivizes risk by keeping going in a particular direction without turning
	return (runLength * (runLength + 1)) / 2;
}

void JetLag2021Application::SetNextDirection(int nextDirection)
{
	if (nextDirection != direction)
	{
		score += CalculateScoreFromRunLength(runLength);
		runLength = Constants::Game::InitialValues::RUN_LENGTH;
		PlaySound(turnSound);
		direction = nextDirection;
	}
}

bool JetLag2021Application::HandleInPlayKeyDown(SDL_Keycode sym)
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

bool JetLag2021Application::HandleGameOverKeyDown(SDL_Keycode sym)
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


bool JetLag2021Application::HandleKeyDown(SDL_Keycode sym)
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

bool JetLag2021Application::OnEvent(const SDL_Event& evt)
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

void JetLag2021Application::UpdateTail()
{
	for (size_t row = 0; row < tail.size() - 1; ++row)
	{
		tail[row] = tail[row + 1];
	}
	tail[tail.size() - 1] = tail[tail.size() - 1] + direction;
}

void JetLag2021Application::UpdateBlocks()
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

void JetLag2021Application::UpdateGameStatus()
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
		if (pickUps[tail.size() - 1] == tail[tail.size() - 1])
		{
			pickUps[tail.size() - 1] = Constants::PickUp::INITIAL_COLUMN;
			score += Constants::PickUp::SCORE_BONUS;
			PlaySound(chompSound);
		}
		runLength++;
	}
}

void JetLag2021Application::UpdateBoard()
{
	if (!gameOver)
	{
		UpdateTail();
		UpdateBlocks();
		UpdatePickUps();
		UpdateGameStatus();
	}
}

void JetLag2021Application::Update(int milliseconds)
{
	counter += milliseconds;
	while (counter > Constants::Game::FRAME_MILLISECONDS)
	{
		UpdateBoard();
		counter -= Constants::Game::FRAME_MILLISECONDS;
	}
}

void JetLag2021Application::DrawBackground()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());
}

void JetLag2021Application::DrawTail()
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

void JetLag2021Application::PlotCellRect(SDL_Rect& rc, int column, int row)
{
	rc.x = column * Constants::Cell::WIDTH;
	rc.y = row * Constants::Cell::HEIGHT;
	rc.w = Constants::Cell::WIDTH;
	rc.h = Constants::Cell::HEIGHT;
}

void JetLag2021Application::DrawBlocks()
{
	for (int row = 0; row < blocks.size(); ++row)
	{
		DrawCharacter(blocks[row], row, (char)0xdb, Constants::Color::WHITE);
	}
}

void JetLag2021Application::DrawWalls()
{
	for (int row = 0; row < blocks.size(); ++row)
	{
		DrawCharacter(Constants::Board::LEFT_WALL, row, (char)0xdb, Constants::Color::BLUE);
		DrawCharacter(Constants::Board::RIGHT_WALL, row, (char)0xdb, Constants::Color::BLUE);
	}
}

void JetLag2021Application::DrawScore()
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

void JetLag2021Application::DrawMuteHint()
{
	if (muted)
	{
		DrawCenteredText(Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::UNMUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
	else
	{
		DrawCenteredText(Constants::UI::MUTE_MESSAGE_ROW, Constants::UI::MUTE_HINT_TEXT, Constants::Color::MAGENTA);
	}
}

void JetLag2021Application::DrawStartHint()
{
	DrawCenteredText(Constants::UI::START_MESSAGE_ROW, Constants::UI::START_HINT_TEXT, Constants::Color::MAGENTA);
}

void JetLag2021Application::DrawHints()
{
	if (gameOver)
	{
		DrawMuteHint();
		DrawStartHint();
	}
}

void JetLag2021Application::Draw()
{
	DrawBackground();
	DrawPickUps();
	DrawBlocks();
	DrawWalls();
	DrawTail();
	DrawScore();
	DrawHints();
}


void JetLag2021Application::ResetGame()
{
	pickUps.clear();
	while (pickUps.size() < Constants::Board::ROWS)
	{
		pickUps.push_back(Constants::PickUp::INITIAL_COLUMN);
	}

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

void JetLag2021Application::RestartGame()
{
	ResetGame();
	gameOver = false;
}

void JetLag2021Application::DrawCenteredText(int row, const std::string& text, const SDL_Color& color)
{
	//you center things by dividing by 2
	DrawText((Constants::Board::COLUMNS - (int)text.size()) / 2, row, text, color);
}

void JetLag2021Application::DrawCharacter(int column, int row, char character, const SDL_Color& color)
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

void JetLag2021Application::DrawText(int column, int row, const std::string& text, const SDL_Color& color)
{
	for (auto ch : text)
	{
		DrawCharacter(column, row, ch, color);
		column++;
	}
}
void JetLag2021Application::PlaySound(Mix_Chunk* chunk)
{
	if (!muted)
	{
		Mix_PlayChannel(Constants::Utility::ANY_CHANNEL, chunk, Constants::Utility::NO_LOOPS);
	}
}

void JetLag2021Application::DrawPickUps()
{
	for (int row = 0; row < pickUps.size(); ++row)
	{
		DrawCharacter(pickUps[row], row, (char)0x04, Constants::Color::YELLOW);
	}

}

void JetLag2021Application::UpdatePickUps()
{
	for (size_t row = 0; row < pickUps.size() - 1; ++row)
	{
		pickUps[row] = pickUps[(size_t)(row + 1)];
	}
	pickUps[pickUps.size() - 1] =
		rand() %
		(Constants::PickUp::MAXIMUM_RANDOM_COLUMN -
			Constants::PickUp::MINIMUM_RANDOM_COLUMN +
			1) +
		Constants::PickUp::MINIMUM_RANDOM_COLUMN;

}