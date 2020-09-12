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

		inline std::tuple<Vector2D_t, Vector2D_t> GetCorners() const { return {m_topLeftCorner, m_bottomRightCorner}; }

		void Reset();

	protected:
		std::map<Vector2D_t, MapSpace> m_mapData{};
		Vector2D_t m_topLeftCorner{};
		Vector2D_t m_bottomRightCorner{};
	};
}