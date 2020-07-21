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
			// get all position and velocity components, then add velocity to position
			// TODO: do we reset velocity here? Might be a good idea
			// TODO: likely change this to a message such that only entities with velocities != 0 get called, make this more efficient
			// TODO: ensure movement is valid (though this may involve other components, such as a collision handler system/component
			auto [pos, vel] = comps.get<PositionComponent, VelocityComponent>(entity);
			pos.position = pos.position + vel.velocity;
		}
	}
}