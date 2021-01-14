#pragma once
#include <string>
#include "Board.h"
namespace Constants::UI
{
	static const int START_MESSAGE_ROW = Constants::Board::ROWS - 1;
	static const int MUTE_MESSAGE_ROW = Constants::Board::ROWS - 2;
	static const std::string MUTE_HINT_TEXT = "<M> to mute";
	static const std::string UNMUTE_HINT_TEXT = "<M> to unmute";
	static const std::string START_HINT_TEXT = "Press <SPACE> to Start!";
}

