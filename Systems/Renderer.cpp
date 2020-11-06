/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Renderer.hpp"
#include "libtcod/libtcod.hpp"
#include "PositionComponent.hpp"
#include "RenderComponent.hpp"

namespace kage
{
	Renderer::Renderer()
	{

	}

	void Renderer::RenderActors(std::shared_ptr<entt::registry> reg) const
	{
		// get all entities with a Position and Render component
		auto comps = reg->view<PositionComponent, RenderComponent>();

		for (auto entity : comps)
		{
			// go through and display any entity with position + render components
			const auto [movement, render] = comps.get<PositionComponent, RenderComponent>(entity);
			Vector2D_t renderPosition = { 0, 0 };
			if (WorldPositionToScreenPosition({ movement.position.x, movement.position.y }, renderPosition))
			{
				// display the character, then make the foreground color correct. Do it in this order to display correctly.
				// doing it this way allowed the background color to not be changed
				TCODConsole::root->putChar(renderPosition.x, renderPosition.y, render.displayCharacter);
				TCODConsole::root->setCharForeground(renderPosition.x, renderPosition.y, render.foregroundColor);
			}
		}
	}

	void Renderer::SetRenderSpace(Vector2D_t tl, Vector2D_t br)
	{
		m_renderSpaceTopLeft = tl;
		m_renderSpaceBottomRight = br;
	}

	void Renderer::RenderWorld(std::shared_ptr<entt::registry> reg) const
	{
		// for now we're just rendering a dark grey screen. Will eventually load the map and draw what is appropriate
		for (int y = m_renderSpaceTopLeft.y; y <= m_renderSpaceBottomRight.y; ++y)
		{
			for (int x = m_renderSpaceTopLeft.x; x <= m_renderSpaceBottomRight.x; ++x)
			{
				// if the world uses any characters (i.e. for "texture" or something like that), do that here with putChar
				TCODConsole::root->setCharBackground(x, y, TCODColor::darkerGrey);
			}
		}
	}

	// TODO: make this the only render function?
	void Renderer::RenderAll(std::shared_ptr<entt::registry> reg) const
	{
		// TODO: somewhere check FoV if decide to go that route

		// render world first, then actors, so actors appear on top of the world.
		// we could do some sort of basic frustrum culling here, but that seems over-the-top for just an ASCII-art game
		// though it could be a fun excercise for later :)
		RenderWorld(reg);
		RenderActors(reg);
	}

	bool Renderer::WorldPositionToScreenPosition(Vector2D_t worldPosition, Vector2D_t& screenPosition) const
	{
		// TODO: this function is going to need a LOT of work in the long run. 
		// For now, just getting it here somewhat as a placeholder

		// translate to possible screen position
		Vector2D_t possibleScreenPosition = worldPosition;

		// check that screen position is within the screen limits
		if (possibleScreenPosition.x < m_renderSpaceTopLeft.x ||
			possibleScreenPosition.y < m_renderSpaceTopLeft.y ||
			possibleScreenPosition.x > m_renderSpaceBottomRight.x ||
			possibleScreenPosition.y > m_renderSpaceBottomRight.y)
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