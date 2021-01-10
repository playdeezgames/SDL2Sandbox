#include "JetLag2021Application.h"
#include "SDL_image.h"
#include "Utility.h"
typedef struct
{
	bool muted;
} GameOptions;

JetLag2021Application JetLag2021Application::sandboxApplication;

JetLag2021Application::JetLag2021Application()
	: Application(Constants::Window::WIDTH, Constants::Window::HEIGHT, Constants::Window::TITLE)
	, soundManager()
	, gameData()

	, romfontTexture(nullptr)
	, romfontSrcRects()
	, joystick(nullptr)
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
		options.muted = soundManager.IsMuted();
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
			soundManager.SetMuted(options.muted);
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
	soundManager.Add(Constants::Sound::CHOMP, Constants::Sound::CHOMP);
	soundManager.Add(Constants::Sound::DEATH, Constants::Sound::DEATH);
	soundManager.Add(Constants::Sound::TURN, Constants::Sound::TURN);
	gameData.ResetGame();
	if (SDL_NumJoysticks() > 0)
	{
		joystick = SDL_JoystickOpen(0);
	}
}

void JetLag2021Application::Finish()
{
	soundManager.Finish();
	SDL_DestroyTexture(romfontTexture);
	if (joystick)
	{
		SDL_JoystickClose(joystick);
		joystick = nullptr;
	}
	IMG_Quit();
}

void JetLag2021Application::SetNextDirection(int nextDirection)
{
	if (gameData.SetNextDirection(nextDirection))
	{
		soundManager.Play(Constants::Sound::TURN);
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
		gameData.RestartGame();
	}
	else if (sym == SDLK_m)
	{
		soundManager.SetMuted(!soundManager.IsMuted());
		SaveOptions();
	}
	return true;
}


bool JetLag2021Application::HandleKeyDown(SDL_Keycode sym)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayKeyDown(sym);
	}
	else
	{
		return HandleGameOverKeyDown(sym);
	}
}

bool JetLag2021Application::HandleInPlayJoyButtonDown(SDL_JoystickID which, Uint8 button)
{
	return true;
}

bool JetLag2021Application::HandleGameOverJoyButtonDown(SDL_JoystickID, Uint8)
{
	gameData.RestartGame();
	return true;
}


bool JetLag2021Application::HandleJoyButtonDown(SDL_JoystickID which, Uint8 button)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayJoyButtonDown(which, button);
	}
	else
	{
		return HandleGameOverJoyButtonDown(which, button);
	}
}

bool JetLag2021Application::HandleInPlayJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	if (axis == 0)
	{
		if (value <= -16384)
		{
			SetNextDirection(Constants::Game::Direction::LEFT);
		}
		else if (value >= 16384)
		{
			SetNextDirection(Constants::Game::Direction::RIGHT);
		}
	}
	return true;
}

bool JetLag2021Application::HandleGameOverJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	return true;
}


bool JetLag2021Application::HandleJoyAxisMotion(SDL_JoystickID which, Uint8 axis, Sint16 value)
{
	if (!gameData.IsGameOver())
	{
		return HandleInPlayJoyAxisMotion(which, axis, value);
	}
	else
	{
		return HandleGameOverJoyAxisMotion(which, axis, value);
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
	case SDL_JOYBUTTONDOWN:
		return HandleJoyButtonDown(evt.jbutton.which, evt.jbutton.button);
	case SDL_JOYAXISMOTION:
		return HandleJoyAxisMotion(evt.jaxis.which, evt.jaxis.axis, evt.jaxis.value);
	default:
		return true;
	}
}

void JetLag2021Application::Update(int milliseconds)
{
	gameData.Update(milliseconds);
}

void JetLag2021Application::DrawBackground()
{
	SDL_SetRenderDrawColor(GetMainRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetMainRenderer());
}

void JetLag2021Application::DrawTail()
{
	for (int row = 0; row < gameData.GetTailLength() - 1; ++row)
	{
		DrawCharacter(gameData.GetTailPosition(row), row, '*', Constants::Color::BROWN);
	}
	if (gameData.IsDead())
	{
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x0F', Constants::Color::RED);
	}
	else
	{
		DrawCharacter(gameData.GetTailPosition(gameData.GetTailLength() - 1), (int)gameData.GetTailLength() - 1, '\x02', Constants::Color::WHITE);
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
	for (int row = 0; row < gameData.GetBlockCount(); ++row)
	{
		DrawCharacter(gameData.GetBlockPosition(row), row, (char)0xdb, Constants::Color::WHITE);
	}
}

void JetLag2021Application::DrawWalls()
{
	for (int row = 0; row < Constants::Board::ROWS; ++row)
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
	int temp = gameData.GetScore();
	while (temp >= Constants::Game::SCORE_RADIX)
	{
		digits++;
		temp /= Constants::Game::SCORE_RADIX;
		rc.x += Constants::Cell::WIDTH;
	}
	temp = gameData.GetScore();
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
	if (soundManager.IsMuted())
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
	if (gameData.IsGameOver())
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

void JetLag2021Application::DrawPickUps()
{
	for (int row = 0; row < gameData.GetPickUpCount(); ++row)
	{
		DrawCharacter(gameData.GetPickUpPosition(row), row, (char)0x04, Constants::Color::YELLOW);
	}

}

