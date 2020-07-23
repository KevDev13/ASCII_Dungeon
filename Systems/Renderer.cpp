/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "libtcod/libtcod.hpp"
#include "Renderer.hpp"
#include "PositionComponent.hpp"
#include "RenderComponent.hpp"

namespace asciidungeon
{
	Renderer::Renderer()
	{

	}

	void Renderer::RenderActors(std::shared_ptr<entt::registry> reg) const
	{
		auto comps = reg->view<PositionComponent, RenderComponent>();

		for (auto entity : comps)
		{
			// go through and display any entity with position + render components
			// TODO: map world coordinates to screen coordinates (do this here or somewhere else?
			const auto [movement, render] = comps.get<PositionComponent, RenderComponent>(entity);
			Vector2D_t renderPosition = { 0, 0 };
			if (WorldPositionToScreenPosition({ movement.position.x, movement.position.y }, renderPosition))
			{
				TCODConsole::root->putCharEx(renderPosition.x, renderPosition.y, render.displayCharacter, render.foregroundColor, render.backgroundColor);
			}
		}
	}

	void Renderer::RenderWorld(std::shared_ptr<entt::registry> reg) const
	{
		
	}

	// TODO: make this the only render function?
	void Renderer::RenderAll(std::shared_ptr<entt::registry> reg) const
	{
		RenderWorld(reg);
		RenderActors(reg);
	}

	bool Renderer::WorldPositionToScreenPosition(Vector2D_t worldPosition, Vector2D_t& screenPosition) const
	{
		// TODO: thos function is going to need a LOT of work in the long run. 
		// For now, just getting it here somewhat as a placeholder

		// translate to possible screen position
		Vector2D_t possibleScreenPosition = worldPosition;

		// check that screen position is within the screen limits
		if (possibleScreenPosition.x < MAP_UPPER_LEFT_CORNER.x ||
			possibleScreenPosition.y < MAP_UPPER_LEFT_CORNER.y ||
			possibleScreenPosition.x > MAP_LOWER_RIGHT_CORNER.x ||
			possibleScreenPosition.y > MAP_LOWER_RIGHT_CORNER.y)
		{
			return false;
		}

		screenPosition = possibleScreenPosition;
		return true;
	}

	Renderer::~Renderer()
	{

	}
}