/*
MovementComponent structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "Vector2D.hpp"

namespace asciidungeon
{
	struct PositionComponent
	{
		Vector2D_t position;

		PositionComponent() = default;
		PositionComponent(Vector2D_t pos) : position(pos) {};
		PositionComponent(int pos_x, int pos_y) : position({ pos_x, pos_y }) {};
	};
}