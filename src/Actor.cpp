/*
Actor class. Used for any object in the game (items on the ground, enemies, player, etc).

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Actor.hpp"
#include "libtcod.h"

namespace AsciiDungeon
{
	Actor::Actor()
	{
		m_currentPosition.x = 0;
		m_currentPosition.y = 0;

		m_displayCharacter = ' ';

		m_currentHealth = 1;
		m_maxHealth = 1;
	}

	Actor::Actor(Vector2D_t pos, char dispCh, int maxHealth) :
		m_currentPosition(pos), m_displayCharacter(dispCh), m_currentHealth(maxHealth), m_maxHealth(maxHealth)
	{

	}

	void Actor::UpdateHealth(int hp)
	{
		if (m_currentHealth + hp > m_maxHealth)
		{
			m_currentHealth = m_maxHealth;
		}
		else
		{
			m_currentHealth += hp;
		}
	}

	void Actor::SetHealth(int hp)
	{
		if (hp > m_maxHealth)
		{
			m_currentHealth = m_maxHealth;
		}
		else
		{
			m_currentHealth = hp;
		}
	}

	void Actor::SetPosition(Vector2D_t pos, bool checkBoundary)
	{
		if (checkBoundary)
		{
			if (CheckMoveBoundary(pos))
			{
				m_currentPosition = pos;
			}
		}
		else
		{
			m_currentPosition = pos;
		}
	}

	void Actor::Move(Vector2D_t pos)
	{
		Vector2D_t newPos = m_currentPosition + pos;
		if (!CheckMoveBoundary(newPos))
		{
			return;
		}

		m_currentPosition = newPos;
	}

	void Actor::Move(int x, int y)
	{
		Move(Vector2D_t{ x, y });
	}

	void Actor::MoveUp()
	{
		Move(0, -1);
	}

	void Actor::MoveDown()
	{
		Move(0, 1);
	}

	void Actor::MoveLeft()
	{
		Move(-1, 0);
	}

	void Actor::MoveRight()
	{
		Move(1, 0);
	}

	bool Actor::CheckMoveBoundary(Vector2D_t newPos)
	{
		if (newPos.x < MAP_UPPER_LEFT_CORNER.x || newPos.x > MAP_LOWER_RIGHT_CORNER.x)
		{
			return false;
		}

		if (newPos.y < MAP_UPPER_LEFT_CORNER.x || newPos.y > MAP_LOWER_RIGHT_CORNER.y)
		{
			return false;
		}

		return true;
	}

	Actor::~Actor() {}
}