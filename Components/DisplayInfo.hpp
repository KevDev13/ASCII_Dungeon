/*
Display info. Used for displaying info on GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <string>

namespace kage
{
	struct DisplayInfo
	{
		std::string name;
		
		DisplayInfo() = default;
		DisplayInfo(std::string n) : name(n) {}
	};
}