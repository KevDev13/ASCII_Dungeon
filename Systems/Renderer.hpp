/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "entt/entt.hpp"
#include "Vector2D.hpp"

namespace kage
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void RenderAll(std::shared_ptr<entt::registry> reg) const;

		void SetRenderSpace(Vector2D_t tl, Vector2D_t br);
		std::tuple<Vector2D_t, Vector2D_t> GetRenderSpace() const { return { m_renderSpaceTopLeft, m_renderSpaceBottomRight }; }

	protected:
		// takes in worldPosition and translates that into the screen coordinates. Returns true if the screen coordinate is valid and should be rendered, false otherwise.
		bool WorldPositionToScreenPosition(Vector2D_t worldPosition, Vector2D_t& screenPosition) const;

		void RenderActors(std::shared_ptr<entt::registry> reg) const;
		void RenderWorld(std::shared_ptr<entt::registry> reg) const;

		Vector2D_t m_renderSpaceTopLeft;
		Vector2D_t m_renderSpaceBottomRight;
	};

}