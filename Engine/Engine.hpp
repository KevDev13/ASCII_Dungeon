/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "entt/entt.hpp"
#include "Renderer.hpp"

namespace asciidungeon
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Main();

		inline bool PlayerWantsToQuit() const { return m_playerWantsToQuit; }

	protected:
		bool m_initialized;
		bool m_playerWantsToQuit;

		std::shared_ptr<entt::registry> m_registry;
		std::unique_ptr<Renderer> m_renderer;

		entt::entity m_playerEntity;

		void HandleInput();
		bool Render();
	};

}
