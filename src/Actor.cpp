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
	}

	Actor::Actor(Position_t pos) :
		m_currentPosition(pos)
	{

	}

	void Actor::MovePosition(Direction pos)
	{
		switch (pos)
		{
			case Direction::UP:
				--m_currentPosition.y;
				return;
			case Direction::DOWN:
				++m_currentPosition.y;
				return;
			case Direction::LEFT:
				--m_currentPosition.x;
				return;
			case Direction::RIGHT:
				++m_currentPosition.x;
				return;
			default:
				break;
		}
	}

	Actor::~Actor() {}
}