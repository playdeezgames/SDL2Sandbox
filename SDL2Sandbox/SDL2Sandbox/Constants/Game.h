#pragma once
#include <string>
#include "SDL.h"
namespace Constants::Game
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
		const bool DEAD = false;
		const int INVINCIBILITY = 0;
		const int POWERUP_COUNTER = 0;
		const bool KEYS_REVERSED = false;
		const int BOMBS = 3;
		const int LIVES = 3;
		const int SCORE_MULTIPLIER = 1;
		const int SCORE_DIVISOR = 1;
		const int SHIELD = 0;
	}
	namespace Counters
	{
		const int SCROLL = 100;
		const int SLOW_SCROLL = 200;
		const int FAST_SCROLL = 50;
		const int INVINCIBILITY = 64;
		const int INVINCIBILITY_WEAR_OFF = 8;
	}
	const int BLOCK_EAT_SCORE = 10;
	const int SCORE_RADIX = 10;
}
