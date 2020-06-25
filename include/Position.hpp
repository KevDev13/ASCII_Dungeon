/*
Position structure
Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

namespace AsciiDungeon
{
	struct Position_t
	{
		int x;
		int y;
	};

	Position_t operator+ (const Position_t& left, const Position_t& right)
	{
		return Position_t { left.x + right.x, left.y + right.y };
	}
}