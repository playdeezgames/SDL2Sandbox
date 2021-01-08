#pragma once
#include <string>
#include "SDL.h"
class GameConstants
{
public:
	class Board
	{
	public:
		static const int COLUMNS = 40;
		static const int ROWS = 30;
	};
	class Cell
	{
	public:
		static const int WIDTH = 16;
		static const int HEIGHT = 16;
	};
	static const int WINDOW_WIDTH = Board::COLUMNS * Cell::WIDTH;
	static const int WINDOW_HEIGHT = Board::ROWS * Cell::HEIGHT;
	static const int BLOCK_INITIAL_COLUMN = 0;
	static const int BLOCK_MINIMUM_RANDOM_COLUMN = 1;
	static const int BLOCK_MAXIMUM_RANDOM_COLUMN = Board::COLUMNS - 2;
	static const int FRAME_MILLISECONDS = 100;
	static const int TAIL_LENGTH = 6;
	static const int TAIL_INITIAL_COLUMN = Board::COLUMNS / 2;
	static const std::string WINDOW_TITLE;
	static const std::string OPTIONS_FILE_NAME;
	static const std::string OPTIONS_WRITE_MODE;
	static const std::string OPTIONS_READ_MODE;
	static const std::string ROMFONT_IMAGE_FILE_NAME;
	static const std::string TURN_SOUND_FILE_NAME;
	static const std::string DEATH_SOUND_FILE_NAME;
	static const int DIRECTION_LEFT = -1;
	static const int DIRECTION_RIGHT = 1;
	static const int INITIAL_RUN_LENGTH = 0;
	static const int INITIAL_SCORE = 0;
	static const int OPTIONS_RECORD_COUNT = 1;
	static const int ROMFONT_COLUMNS = 16;
	static const int ROMFONT_ROWS = 16;
	static const int ROMFONT_CELL_COUNT = ROMFONT_COLUMNS * ROMFONT_ROWS;
	static const int ROMFONT_CELL_WIDTH = Cell::WIDTH;
	static const int ROMFONT_CELL_HEIGHT = Cell::HEIGHT;
	static const int ANY_CHANNEL = -1;
	static const int NO_LOOPS = 0;
	static const int DEFAULT_X = 0;
	static const int DEFAULT_Y = 0;
	static const int SCORE_RADIX = 10;
	static const int ROMFONT_DIGITS_ROW = 3;
	static const int INITIAL_COUNTER = 0;
	static const bool INITIAL_GAME_OVER = true;
	static const bool INITIAL_MUTED = false;
	static const bool INITIAL_DEAD = false;
	static const int START_MESSAGE_ROW = Board::ROWS - 1;
	static const int MUTE_MESSAGE_ROW = Board::ROWS - 2;
	static const std::string MUTE_HINT_TEXT;
	static const std::string UNMUTE_HINT_TEXT;
	static const std::string START_HINT_TEXT;
	static const SDL_Color DARK_MAGENTA;
	static const SDL_Color BROWN;
	static const SDL_Color WHITE;
	static const SDL_Color RED;
};

