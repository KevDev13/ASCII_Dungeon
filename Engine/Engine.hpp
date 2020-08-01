/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "entt/entt.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"
#include "MovementHandler.hpp"
#include "State.hpp"

namespace asciidungeon
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Main();

	protected:
		bool m_initialized;

		std::shared_ptr<entt::registry> m_registry;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputHandler> m_inputHandler;
		std::unique_ptr<MovementHandler> m_movementHandler;

		entt::entity m_playerEntity;

		bool Render();

		State m_currentState;
	};

}
