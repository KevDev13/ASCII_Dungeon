/*
Actor class. Used for any object in the game (items on the ground, enemies, player, etc).

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "Position.hpp"

namespace AsciiDungeon
{
	class Actor
	{
	public:
		Actor();
		Actor(int x, int y);
		Actor(Position_t pos);
		~Actor();

	protected:
		Position_t m_currentPosition;
	};
}