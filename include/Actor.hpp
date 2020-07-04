/*
Actor class. Used for any object in the game (items on the ground, enemies, player, etc).

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod.h"
#include "Vector2D.hpp"

namespace AsciiDungeon
{
	class Actor
	{
	public:
		Actor();
		Actor(Vector2D_t pos, char dispCh, int maxHealth);
		~Actor();

		void SetPosition(Vector2D_t pos, bool checkBoundary = true);
		inline void SetDisplayCharacter(char ch) { m_displayCharacter = ch; }
		void UpdateHealth(int hp);
		void SetHealth(int hp);
		inline void UpdateMaxHealth(int hp) { m_maxHealth += hp; }
		inline void SetMaxHealth(int hp) { m_maxHealth = hp; }

		void Move(Vector2D_t pos);
		void Move(int x, int y);
		void MoveUp();
		void MoveDown();
		void MoveLeft();
		void MoveRight();

		inline Vector2D_t GetPosition() const { return m_currentPosition; }
		inline char GetDisplayCharacter() const { return m_displayCharacter; }
		inline int GetCurrentHealth() const { return m_currentHealth; }
		inline int GetMaxHealth() const { return m_maxHealth; }

		inline bool IsDead() const { return m_currentHealth <= 0; }

	protected:
		Vector2D_t m_currentPosition;
		char m_displayCharacter;

		int m_maxHealth;
		int m_currentHealth;

		bool CheckMoveBoundary(Vector2D_t newPos);
	};

	extern const Vector2D_t MAP_UPPER_LEFT_CORNER;
	extern const Vector2D_t MAP_LOWER_RIGHT_CORNER;
}