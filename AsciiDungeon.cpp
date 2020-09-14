/*
ASCII Dungeon

A simple dungeon crawler written in libtcod.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Engine.hpp"

const int WINDOW_SIZE_WIDTH = 80;
const int WINDOW_SIZE_HEIGHT = 50;
const std::string WINDOW_TITLE = "ASCII Dungeon";
const bool WINDOW_START_FULLSCREEN = false;
const int MAXIMUM_FRAMES_PER_SECOND = 60;

int main()
{
	std::unique_ptr<gage::Engine> engine = std::make_unique<gage::Engine>();

	if (!engine->SetInitialWindowProperties(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, MAXIMUM_FRAMES_PER_SECOND))
	{
		return 3;
	}

	// initialize engine and if it fails, exit
	if (!engine->Initialize())
	{
		return 1;
	}

	if (!engine->Main())
	{
		return 2;
	}

	return 0;
}