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
		MapSpace ret;
		try
		{
			ret = m_mapData.at(Vector2D_t(x, y));
		}
		catch (std::out_of_range& e)
		{
			return MapSpace();
		}

		return ret;
	}

	bool Map::Set(int x, int y, MapSpace space)
	{
		std::map<Vector2D_t, MapSpace>::iterator iter = m_mapData.find(Vector2D_t(x, y));
		if (iter == m_mapData.end())
		{
			return false;
		}
		iter->second = space;
		return true;
	}

	void Map::Reset()
	{
		m_mapData.clear();
	}
}