/*
Handles movement for all entities

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "MovementHandler.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"

namespace asciidungeon
{
	MovementHandler::MovementHandler()
	{

	}

	MovementHandler::~MovementHandler() {}

	void MovementHandler::ProcessMovement(std::shared_ptr<entt::registry> reg) const
	{
		auto comps = reg->view<PositionComponent, VelocityComponent>();

		for (auto entity : comps)
		{
			auto [movement, vel] = comps.get<PositionComponent, VelocityComponent>(entity);
			movement.position = movement.position + vel.velocity;
		}
	}
}