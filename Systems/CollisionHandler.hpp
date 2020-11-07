/*
Detects collisions and prevents the player or NPC from moving if a collision is detected

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "entt/entt.hpp"

namespace kage
{
	class CollisionHandler
	{
	public:
		CollisionHandler();
		~CollisionHandler();

		void DetectCollisions(std::shared_ptr<entt::registry> reg);

	protected:

	};
}