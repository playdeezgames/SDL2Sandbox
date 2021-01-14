#pragma once
#include <string>
#include "Cell.h"
namespace Constants::RomFont
{
	const std::string IMAGE_FILE_NAME = "assets/images/romfont8x8.png";
	const int COLUMNS = 16;
	const int ROWS = 16;
	const int CELL_COUNT = COLUMNS * ROWS;
	const int CELL_WIDTH = Constants::Cell::WIDTH;
	const int CELL_HEIGHT = Constants::Cell::HEIGHT;
}

