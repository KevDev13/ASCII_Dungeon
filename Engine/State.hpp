/*
State information for the game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

namespace kage
{
	enum class State
	{
		STARTUP,
		MAIN_MENU,
		PLAYING,
		INVENTORY,
		QUIT
	};
}