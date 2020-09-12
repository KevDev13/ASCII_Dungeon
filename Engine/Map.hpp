/*
Map class, used for the current map where the player is located.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <map>

#include "Vector2D.hpp"
#include "MapSpace.hpp"

namespace gage
{
	class Map
	{
	public:
		Map();
		~Map();

		bool Load(std::string fileName);

		MapSpace At(int x, int y) const;
		bool Set(int x, int y, MapSpace space);

		void Reset();

	protected:
		std::map<Vector2D_t, MapSpace> m_mapData;
	};
}