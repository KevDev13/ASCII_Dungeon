/*
Map class, used for the current map where the player is located.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Map.hpp"

namespace gage
{
	Map::Map()
	{

	}

	Map::~Map()
	{

	}

	bool Map::Load(std::string fileName)
	{
		return true;
	}

	MapSpace Map::At(int x, int y) const
	{
		return m_mapData[x][y];
	}

	bool Map::Set(int x, int y, MapSpace space)
	{
		if (x >= m_mapData.size() || y >= m_mapData[x].size())
		{
			return false;
		}
		m_mapData[x][y] = space;
		return true;
	}

	void Map::Reset()
	{
		m_mapData.clear();
	}
}