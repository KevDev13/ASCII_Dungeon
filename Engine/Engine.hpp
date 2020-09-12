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
#include "GUI.hpp"
#include "Map.hpp"
#include "MapSpace.hpp"

namespace gage
{
	class Engine
	{
		// put any constants needed in the .hpp file here, otherwise everything goes after the public items
	protected:
		// default max frames per second
		const static int DEFAULT_MAX_FPS = 60;

	public:
		Engine();
		~Engine();

		bool SetInitialWindowProperties(int w, int h, std::string title, bool startFullscreen = false, int maxFps = DEFAULT_MAX_FPS);
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
		// main registry containing all components
		std::shared_ptr<entt::registry> m_registry;

		// Systems
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputHandler> m_inputHandler;
		std::unique_ptr<MovementHandler> m_movementHandler;

		// Player entity
		entt::entity m_playerEntity;
		const char PLAYER_DISPLAY_CHAR = 1;	// 1 = smiley face with the png/bitmap_col.png file.

		// mouse entity
		entt::entity m_mouseEntity;

		// current game state - will likely be moved to the main() eventually
		State m_currentState;

		// TODO: delete this eventually, OR change it so it renders correctly based off of game state (m_currentState)
		bool Render();
		
		// GUI class
		std::unique_ptr<GUI> m_gui;

		// version info
		const int VERSION_MAJOR = 0;
		const int VERSION_MINOR = 0;
		const int VERSION_BUILD = 2;
		std::string BuildVerionString();

		// current loaded map
		std::shared_ptr<Map> m_currentMap;
	};

}
