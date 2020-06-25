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
		Actor(Position_t pos, char dispCh);
		~Actor();

		inline void SetPosition(Position_t pos) { m_currentPosition = pos; }
		inline void Move(Position_t pos) { m_currentPosition = m_currentPosition + pos; }
		inline void Move(int x, int y) { Move(Position_t{ x, y }); }
		inline void SetDisplayCharacter(char ch) { m_displayCharacter = ch; }
		inline void MoveUp() { --m_currentPosition.y; }
		inline void MoveDown() { ++m_currentPosition.y; }
		inline void MoveLeft() { --m_currentPosition.x; }
		inline void MoveRight() { ++m_currentPosition.x; }

		inline Position_t GetPosition() const { return m_currentPosition; }
		inline char GetDisplayCharacter() const { return m_displayCharacter; }

	protected:
		Position_t m_currentPosition;
		char m_displayCharacter;
	};
}