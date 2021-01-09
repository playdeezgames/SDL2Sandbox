#pragma once
#include <string>
#include "SDL.h"
namespace Constants
{
	namespace Board
	{
		const int COLUMNS = 40;
		const int ROWS = 30;
		const int LEFT_WALL = 0;
		const int RIGHT_WALL = Constants::Board::COLUMNS - 1;
	}
	namespace Block
	{
		const int INITIAL_COLUMN = 0;
		const int MINIMUM_RANDOM_COLUMN = 1;
		const int MAXIMUM_RANDOM_COLUMN = Constants::Board::COLUMNS - 2;
	}
	namespace Cell
	{
		const int WIDTH = 16;
		const int HEIGHT = 16;
	}
	namespace Window
	{
		const int WIDTH = Constants::Board::COLUMNS * Constants::Cell::WIDTH;
		const int HEIGHT = Constants::Board::ROWS * Constants::Cell::HEIGHT;
		const std::string TITLE = "JetLag 2021";
	}
	namespace Color
	{
		const SDL_Color MAGENTA = { 0xAA, 0x00, 0xAA, 0xFF };
		const SDL_Color BROWN = { 0xAA, 0x55, 0x00, 0xFF };
		const SDL_Color WHITE = { 0xFF, 0xFF, 0xFF, 0xFF };
		const SDL_Color RED = { 0xAA, 0x00, 0x00, 0xFF };
		const SDL_Color BLUE = { 0x00, 0x00, 0xAA, 0xFF };
	}
}
class GameConstants
{
public:
	static const int FRAME_MILLISECONDS = 100;

	static const int TAIL_LENGTH = 6;
	static const int TAIL_INITIAL_COLUMN = Constants::Board::COLUMNS / 2;

	static const std::string OPTIONS_FILE_NAME;
	static const std::string OPTIONS_WRITE_MODE;
	static const std::string OPTIONS_READ_MODE;
	static const int OPTIONS_RECORD_COUNT = 1;

	static const std::string TURN_SOUND_FILE_NAME;
	static const std::string DEATH_SOUND_FILE_NAME;

	static const int DIRECTION_LEFT = -1;
	static const int DIRECTION_RIGHT = 1;

	static const int INITIAL_RUN_LENGTH = 0;
	static const int INITIAL_SCORE = 0;
	static const int INITIAL_COUNTER = 0;
	static const bool INITIAL_GAME_OVER = true;
	static const bool INITIAL_MUTED = false;
	static const bool INITIAL_DEAD = false;

	static const std::string ROMFONT_IMAGE_FILE_NAME;
	static const int ROMFONT_COLUMNS = 16;
	static const int ROMFONT_ROWS = 16;
	static const int ROMFONT_CELL_COUNT = ROMFONT_COLUMNS * ROMFONT_ROWS;
	static const int ROMFONT_CELL_WIDTH = Constants::Cell::WIDTH;
	static const int ROMFONT_CELL_HEIGHT = Constants::Cell::HEIGHT;

	static const int ANY_CHANNEL = -1;
	static const int NO_LOOPS = 0;
	static const int DEFAULT_X = 0;
	static const int DEFAULT_Y = 0;
	static const int SCORE_RADIX = 10;
	static const int START_MESSAGE_ROW = Constants::Board::ROWS - 1;
	static const int MUTE_MESSAGE_ROW = Constants::Board::ROWS - 2;
	static const std::string MUTE_HINT_TEXT;
	static const std::string UNMUTE_HINT_TEXT;
	static const std::string START_HINT_TEXT;
};

