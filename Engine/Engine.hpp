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

namespace gage
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool SetInitialWindowProperties(int w, int h, std::string title, bool startFullscreen = false, int maxFps = 60);
		bool Initialize();
		bool Main();

	protected:
		bool m_initialized;
		
		// window properties
		int m_windowHeight;
		int m_windowWidth;
		std::string m_windowTitle;
		bool m_windowFullscreen;

		int m_maxFps;

		// ECS stuff
		std::shared_ptr<entt::registry> m_registry;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputHandler> m_inputHandler;
		std::unique_ptr<MovementHandler> m_movementHandler;

		// Player entity
		entt::entity m_playerEntity;

		// current game state - will likely be moved to the main() eventually
		State m_currentState;

		// TODO: delete this eventually
		bool Render();

		// version info
		const int VERSION_MAJOR = 0;
		const int VERSION_MINOR = 0;
		const int VERSION_BUILD = 1;
	};

}
