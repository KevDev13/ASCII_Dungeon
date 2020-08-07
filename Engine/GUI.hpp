/*
GUI class

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod/libtcod.hpp"
#include "Vector2D.hpp"

namespace gage
{
	class GUI
	{
	public:
		GUI();
		~GUI();

		void DrawRectangle(Vector2D_t upperLeft, Vector2D_t lowerRight) const;
		void DisplayFPS(Vector2D_t startPoint) const;
		void DisplayVersionInfo(Vector2D_t startPoint, const int major, const int minor, const int build) const;
	};
}