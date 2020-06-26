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
	}

	Actor::Actor(Position_t pos, char dispCh) :
		m_currentPosition(pos), m_displayCharacter(dispCh)
	{

	}

	void Actor::SetPosition(Position_t pos, bool checkBoundary)
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

	void Actor::Move(Position_t pos)
	{
		Position_t newPos = m_currentPosition + pos;
		if (!CheckMoveBoundary(newPos))
		{
			return;
		}

		m_currentPosition = newPos;
	}

	void Actor::Move(int x, int y)
	{
		Move(Position_t{ x, y });
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

	bool Actor::CheckMoveBoundary(Position_t newPos)
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