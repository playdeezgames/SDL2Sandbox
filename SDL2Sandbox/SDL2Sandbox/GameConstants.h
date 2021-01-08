#pragma once
#include <string>
class GameConstants
{
public:
	static const int BOARD_COLUMNS = 40;
	static const int BOARD_ROWS = 30;
	static const int CELL_WIDTH = 16;
	static const int CELL_HEIGHT = 16;
	static const int WINDOW_WIDTH = BOARD_COLUMNS * CELL_WIDTH;
	static const int WINDOW_HEIGHT = BOARD_ROWS * CELL_HEIGHT;
	static const int BLOCK_INITIAL_COLUMN = 0;
	static const int BLOCK_MINIMUM_RANDOM_COLUMN = 1;
	static const int BLOCK_MAXIMUM_RANDOM_COLUMN = BOARD_COLUMNS - 2;
	static const int FRAME_MILLISECONDS = 100;
	static const int TAIL_LENGTH = 6;
	static const int TAIL_INITIAL_COLUMN = BOARD_COLUMNS / 2;
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
	static const int ROMFONT_CELL_WIDTH = CELL_WIDTH;
	static const int ROMFONT_CELL_HEIGHT = CELL_HEIGHT;
	static const int ANY_CHANNEL = -1;
	static const int NO_LOOPS = 0;
	static const int DEFAULT_X = 0;
	static const int DEFAULT_Y = 0;
	static const int SCORE_RADIX = 10;
	static const int ROMFONT_DIGITS_ROW = 3;
	static const int INITIAL_COUNTER = 0;
	static const bool INITIAL_GAME_OVER = true;
	static const bool INITIAL_MUTED = false;
	static const int START_MESSAGE_ROW = BOARD_ROWS - 1;
	static const int MUTE_MESSAGE_ROW = BOARD_ROWS - 2;
	static const std::string MUTE_HINT_TEXT;
	static const std::string UNMUTE_HINT_TEXT;
	static const std::string START_HINT_TEXT;
};

