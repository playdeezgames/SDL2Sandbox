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
	namespace Tail
	{
		const int LENGTH = 6;
		const int INITIAL_COLUMN = Constants::Board::COLUMNS / 2;

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
	namespace SoundFile
	{
		const std::string TURN = "jl2017turn.wav";
		const std::string DEATH = "jl2017death.wav";
	}
	namespace Game
	{
		namespace Direction
		{
			const int LEFT = -1;
			const int RIGHT = 1;
		}
		namespace InitialValues
		{
			const int RUN_LENGTH = 0;
			const int SCORE = 0;
			const int COUNTER = 0;
			const bool GAME_OVER = true;
			const bool MUTED = false;
			const bool DEAD = false;
		}
		const int FRAME_MILLISECONDS = 100;
		const int SCORE_RADIX = 10;
	}
	namespace Options
	{
		const std::string FILE_NAME = "gameoptions.bin";
		const std::string WRITE_MODE = "wb";
		const std::string READ_MODE = "rb";
		const int RECORD_COUNT = 1;
	}
	namespace RomFont
	{
		const std::string IMAGE_FILE_NAME = "romfont8x8.png";
		const int COLUMNS = 16;
		const int ROWS = 16;
		const int CELL_COUNT = COLUMNS * ROWS;
		const int CELL_WIDTH = Constants::Cell::WIDTH;
		const int CELL_HEIGHT = Constants::Cell::HEIGHT;
	}
	namespace Utility
	{
		const int ANY_CHANNEL = -1;
		const int NO_LOOPS = 0;
		const int DEFAULT_X = 0;
		const int DEFAULT_Y = 0;
	}
	namespace UI
	{
		static const int START_MESSAGE_ROW = Constants::Board::ROWS - 1;
		static const int MUTE_MESSAGE_ROW = Constants::Board::ROWS - 2;
		static const std::string MUTE_HINT_TEXT = "<M> to mute";
		static const std::string UNMUTE_HINT_TEXT = "<M> to unmute";
		static const std::string START_HINT_TEXT = "Press <SPACE> to Start!";
	}
}