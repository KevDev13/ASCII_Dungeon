/*
Actor class. Used for any object in the game (items on the ground, enemies, player, etc).

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod.h"
#include "Position.hpp"

namespace AsciiDungeon
{
	class Actor
	{
	public:
		Actor();
		Actor(Position_t pos, char dispCh);
		~Actor();

		void SetPosition(Position_t pos, bool checkBoundary = true);
		inline void SetDisplayCharacter(char ch) { m_displayCharacter = ch; }

		void Move(Position_t pos);
		void Move(int x, int y);
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		inline Position_t GetPosition() const { return m_currentPosition; }
		inline char GetDisplayCharacter() const { return m_displayCharacter; }

	protected:
		Position_t m_currentPosition;
		char m_displayCharacter;

		bool CheckMoveBoundary(Position_t newPos);
	};

	extern const Position_t MAP_UPPER_LEFT_CORNER;
	extern const Position_t MAP_LOWER_RIGHT_CORNER;
}