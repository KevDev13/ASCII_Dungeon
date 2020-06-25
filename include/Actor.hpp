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
		Actor(Position_t pos);
		~Actor();

		static enum class Direction
		{
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		inline void SetPosition(Position_t pos) { m_currentPosition = pos; }
		inline void MovePosition(Position_t pos) { m_currentPosition = m_currentPosition + pos; }

		void MovePosition(Direction dir);

		Position_t GetPosition() const { return m_currentPosition; }

	protected:
		Position_t m_currentPosition;
	};
}