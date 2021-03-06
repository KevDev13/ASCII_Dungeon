/*
Handles movement for all entities

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "MovementHandler.hpp"
#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"

namespace kage
{
	MovementHandler::MovementHandler()
	{

	}

	MovementHandler::~MovementHandler() {}

	void MovementHandler::ProcessMovement(std::shared_ptr<entt::registry> reg) const
	{
		// get all components with a position and velocity component
		auto comps = reg->view<PositionComponent, VelocityComponent>();

		for (auto entity : comps)
		{
			// get all position and velocity components, then add velocity to position
			// TODO: likely change this to a message such that only entities with velocities != 0 get called, make this more efficient
			auto [pos, vel] = comps.get<PositionComponent, VelocityComponent>(entity);
			pos.position += vel.velocity;

			// set velocity to 0 now that we no longer need it
			vel = { 0, 0 };
		}
	}
}