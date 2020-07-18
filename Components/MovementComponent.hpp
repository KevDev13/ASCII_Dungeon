/*
MovementComponent structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "Vector2D.hpp"

namespace asciidungeon
{
	struct MovementComponent
	{
		Vector2D_t position;
		Vector2D_t velocity;

		MovementComponent() = default;
		MovementComponent(Vector2D_t pos) : position(pos) , velocity({ 0, 0 }) {};
		MovementComponent(Vector2D_t pos, Vector2D_t vel) : position(pos), velocity(vel) {};
		MovementComponent(int pos_x, int pos_y) : position({ pos_x, pos_y }), velocity({ 0, 0 }) {};
		MovementComponent(int pos_x, int pos_y, int vel_x, int vel_y) : position({ pos_x, pos_y }), velocity({ vel_x, vel_y }) {};
	};
}