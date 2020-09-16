/*
MapSpace. Contains all information about a single point on the map.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod/libtcod.hpp"
#include "RenderComponent.hpp"

namespace kage
{
	enum class MapSpaceType
	{
		GROUND,
		WATER,
		WALL,
		DOOR
	};

	struct MapSpace
	{
		RenderComponent renderInformation;
		bool willCollideWith;	// true = player/NPC cannot pass into this square, false = they can
		MapSpaceType type;

		MapSpace() = default;
	};
}