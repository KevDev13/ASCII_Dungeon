/*
List of all constants needed for the game

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod.h"
#include "Position.hpp"

namespace AsciiDungeon
{
	const int VERSION_MAJOR = 0;
	const int VERSION_MINOR = 0;
	const int VERSION_BUILD = 1;

	const int WINDOW_SIZE_HEIGHT = 50;
	const int WINDOW_SIZE_WIDTH = 80;
	const char* WINDOW_TITLE = "ASCII Dungeon";
	const bool WINDOW_START_FULLSCREEN = false;

	const char PLAYER_DISPLAY_CHAR = '@';
	const TCODColor DEFAULT_BACKGROUND_COLOR = TCODColor::black;
	const TCODColor DEFAULT_FOREGROUND_COLOR = TCODColor::yellow;

	const Position_t MAP_UPPER_LEFT_CORNER = { 1, 1 };
	const Position_t MAP_LOWER_RIGHT_CORNER = { 47, 37 };

	namespace PlayerInput
	{
		const char MOVE_UP = 'w';
		const char MOVE_DOWN = 's';
		const char MOVE_LEFT = 'a';
		const char MOVE_RIGHT = 'd';
	}
}