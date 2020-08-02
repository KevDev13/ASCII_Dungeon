/*
Vector2D type structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

namespace asciidungeon
{
	struct Vector2D_t
	{
		int x;
		int y;

		Vector2D_t() = default;
		Vector2D_t(int x_, int y_) : x(x_), y(y_) {}
	};

	inline Vector2D_t operator+ (const Vector2D_t& left, const Vector2D_t& right)
	{
		return Vector2D_t { left.x + right.x, left.y + right.y };
	}

	inline Vector2D_t operator- (const Vector2D_t& left, const Vector2D_t& right)
	{
		return Vector2D_t{ left.x - right.x, left.y - right.y };
	}

	inline Vector2D_t operator* (const Vector2D_t& left, const int& right)
	{
		return Vector2D_t{ left.x * right, left.y * right };
	}

	inline Vector2D_t operator* (const int& left, const Vector2D_t& right)
	{
		return Vector2D_t{ left * right.x, left * right.y };
	}

	inline bool operator== (const Vector2D_t& left, const Vector2D_t& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	inline bool operator!= (const Vector2D_t& left, const Vector2D_t& right)
	{
		return !(left == right);
	}

	// TODO: add += operator
}