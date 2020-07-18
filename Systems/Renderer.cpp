/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "libtcod/libtcod.hpp"
#include "Renderer.hpp"
#include "MovementComponent.hpp"
#include "RenderComponent.hpp"

namespace asciidungeon
{
	Renderer::Renderer()
	{

	}

	void Renderer::RenderActors(std::shared_ptr<entt::registry> reg) const
	{
		auto comps = reg->view<MovementComponent, RenderComponent>();

		for (auto entity : comps)
		{
			auto [movement, render] = comps.get<MovementComponent, RenderComponent>(entity);
			TCODConsole::root->putCharEx(movement.position.x, movement.position.y, render.displayCharacter, render.foregroundColor, render.backgroundColor);
		}
	}

	void Renderer::RenderWorld(std::shared_ptr<entt::registry> reg) const
	{
		
	}

	void Renderer::RenderAll(std::shared_ptr<entt::registry> reg) const
	{
		RenderWorld(reg);
		RenderActors(reg);
	}

	Renderer::~Renderer()
	{

	}
}