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

	inline Position_t operator+ (const Position_t& left, const Position_t& right)
	{
		return Position_t { left.x + right.x, left.y + right.y };
	}

	inline Position_t operator- (const Position_t& left, const Position_t& right)
	{
		return Position_t{ left.x - right.x, left.y - right.y };
	}

	inline Position_t operator* (const Position_t& left, const int& right)
	{
		return Position_t{ left.x * right, left.y * right };
	}

	inline Position_t operator* (const int& left, const Position_t& right)
	{
		return Position_t{ left * right.x, left * right.y };
	}

	inline bool operator== (const Position_t& left, const Position_t& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	inline bool operator!= (const Position_t& left, const Position_t& right)
	{
		return !(left == right);
	}
}