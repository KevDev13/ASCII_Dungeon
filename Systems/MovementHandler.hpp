/*
Handles movement for all entities

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "entt/entt.hpp"

namespace gage
{
	class MovementHandler
	{
	public:
		MovementHandler();
		~MovementHandler();

		void ProcessMovement(std::shared_ptr<entt::registry> reg) const;

	protected:
	};
}