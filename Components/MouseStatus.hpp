/*
Status of the mouse updated with input handler.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "Vector2D.hpp"

namespace gage
{
	struct MouseStatus
	{
		Vector2D_t position;
		bool clicked;

		MouseStatus() = default;
	};
}