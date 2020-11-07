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

		// TODO: Also check map spaces for collisions

		// go through each entity
		for (auto entity : compToCheck)
		{
			// Get position and velocity components
			auto [pos, vel] = compToCheck.get<PositionComponent, VelocityComponent>(entity);
			// if velocity is not already 0, check if collision exists, and if so, set velocity to 0, 0
			if (vel.velocity != Vector2D_t(0, 0))
			{
				Vector2D_t newPosition = pos.position + vel.velocity;
				for (auto entityToCheck : possibleCollisions)
				{
					const auto checkPos = possibleCollisions.get<PositionComponent>(entityToCheck);
					// if collision, set vel to 0
					if (newPosition == checkPos.position)
					{
						vel.velocity = { 0, 0 };
					}
				}
			}
		}
	}
}