#pragma once
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
};

