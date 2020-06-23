/*
ASCII Dungeon

A simple dungeon crawler written in libtcod.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include <memory>

#include "libtcod.h"
#include "Engine.hpp"

using namespace AsciiDungeon;

int main()
{
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	if (!engine->Initialize())
	{
		return 1;
	}
	engine->Main();

	return 0;
}