#pragma once
#include "Board.h"
#include "Cell.h"
namespace Constants::Window
{
	const int WIDTH = Constants::Board::COLUMNS * Constants::Cell::WIDTH;
	const int HEIGHT = Constants::Board::ROWS * Constants::Cell::HEIGHT;
	const std::string TITLE = "JetLag 2021";
}

