/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>
#include <list>

#include "libtcod/libtcod.hpp"
#include "entt/entt.hpp"

namespace asciidungeon
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void RenderActors(std::shared_ptr<entt::registry> reg) const;
		void RenderWorld(std::shared_ptr<entt::registry> reg) const;
		void RenderAll(std::shared_ptr<entt::registry> reg) const;

	protected:
	};

}