/*
List of all constants needed for the game

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod/libtcod.hpp"
#include "Vector2D.hpp"

//extern class TCODColor;

namespace asciidungeon
{
	const int VERSION_MAJOR = 0;
	const int VERSION_MINOR = 0;
	const int VERSION_BUILD = 1;

	const int WINDOW_SIZE_HEIGHT = 50;
	const int WINDOW_SIZE_WIDTH = 80;
	const char* WINDOW_TITLE = "ASCII Dungeon";
	const bool WINDOW_START_FULLSCREEN = false;
	const char* FONT_FILE = "png/bitmap_col.png";

	const char PLAYER_DISPLAY_CHAR = '@';
	const TCODColor DEFAULT_BACKGROUND_COLOR = TCODColor::black;
	const TCODColor DEFAULT_FOREGROUND_COLOR = TCODColor::white;

	const Vector2D_t MAP_UPPER_LEFT_CORNER = { 1, 1 };
	const Vector2D_t MAP_LOWER_RIGHT_CORNER = { 47, 37 };
}