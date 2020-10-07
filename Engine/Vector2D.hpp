/*
Vector2D type structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

namespace kage
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

	inline Vector2D_t& operator+= (Vector2D_t& left, const Vector2D_t& right)
	{
		left = left + right;
		return left;
	}

	inline Vector2D_t& operator-= (Vector2D_t& left, const Vector2D_t& right)
	{
		left = left - right;
		return left;
	}

	// left < right if the vector is above it in the screen (aka smaller y value). If same y, check x.
	inline bool operator< (const Vector2D_t& left, const Vector2D_t& right)
	{
		if (left.y == right.y)
		{
			return left.x < right.x;
		}
		else
		{
			return left.y < right.y;
		}
	}

	inline bool operator<= (const Vector2D_t& left, const Vector2D_t& right)
	{
		return (left < right) || (left == right);
	}

	inline bool operator> (const Vector2D_t& left, const Vector2D_t& right)
	{
		return !(left <= right);
	}

	inline bool operator>= (const Vector2D_t& left, const Vector2D_t& right)
	{
		return !(left < right);
	}
}