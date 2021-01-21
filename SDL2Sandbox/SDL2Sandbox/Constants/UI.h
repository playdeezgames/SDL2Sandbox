#pragma once
#include <string>
#include "Board.h"
namespace Constants::UI
{
	static const int RESTART_MESSAGE_ROW = Constants::Board::ROWS / 2 + 0;
	static const int MENU_MESSAGE_ROW = Constants::Board::ROWS / 2 + 1;
	static const std::string MENU_HINT_TEXT = "<Esc> for Main Menu";
	static const std::string RESTART_HINT_TEXT = "Press <SPACE> to Restart!";
	static const std::string ICON_FILE_NAME = "assets/images/icon.png";
}

