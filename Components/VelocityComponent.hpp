/*
MovementComponent structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "Vector2D.hpp"

namespace asciidungeon
{
	struct VelocityComponent
	{
		Vector2D_t velocity;

		VelocityComponent() = default;
		VelocityComponent(Vector2D_t vel) : velocity(vel) {};
		VelocityComponent(int vel_x, int vel_y) : velocity({ vel_x, vel_y }) {};
	};
}