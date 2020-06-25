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

	Actor::~Actor() {}
}