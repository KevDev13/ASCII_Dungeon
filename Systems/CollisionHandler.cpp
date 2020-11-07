/*
Detects collisions and prevents the player or NPC from moving if a collision is detected

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "CollisionHandler.hpp"

#include "PositionComponent.hpp"
#include "VelocityComponent.hpp"
#include "RenderComponent.hpp"

namespace kage
{
	CollisionHandler::CollisionHandler()
	{

	}

	CollisionHandler::~CollisionHandler()
	{

	}

	void CollisionHandler::DetectCollisions(std::shared_ptr<entt::registry> reg)
	{
		// get all entities with a Position and Velocity component
		auto compToCheck = reg->view<PositionComponent, VelocityComponent>();
		// get possible entities the player/NPC could collide with.
		auto possibleCollisions = reg->view<PositionComponent>();

		// go through each entity
		for (auto entity : compToCheck)
		{
			// Get position and velocity. Position is const so we don't accidentally change it.
			const auto pos = compToCheck.get<PositionComponent>(entity);
			auto vel = compToCheck.get<VelocityComponent>(entity);
			// check if collision exists, and if so, set velocity to 0, 0
			Vector2D_t newPosition = pos.position + vel.velocity;
			for (auto entityToCheck : possibleCollisions)
			{
				const auto checkPos = possibleCollisions.get<PositionComponent>(entityToCheck);
				// if collision, set vel to 0
				if (newPosition == checkPos.position)
				{
					vel = { 0, 0 };
				}
			}
		}
	}
}