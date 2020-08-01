/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Engine.hpp"
#include "libtcod/libtcod.hpp"
#include "Constants.hpp"
#include "PositionComponent.hpp"
#include "RenderComponent.hpp"
#include "VelocityComponent.hpp"

namespace asciidungeon
{
	Engine::Engine()
	{
		m_initialized = false;
		m_playerWantsToQuit = false;

		{
			using namespace std;
			m_registry = make_shared<entt::registry>();
			m_renderer = make_unique<Renderer>();
			m_inputHandler = make_unique<InputHandler>();
			m_movementHandler = make_unique<MovementHandler>();
		}
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::Initialize()
	{
		// setup font file
		TCODConsole::setCustomFont(FONT_FILE);

		// init the window using SDL2
		TCODConsole::initRoot(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, TCOD_RENDERER_SDL2);

		// set maximum FPS
		TCODSystem::setFps(MAXIMUM_FRAMES_PER_SECOND);

		// set default colors
		TCODConsole::root->setDefaultBackground(DEFAULT_BACKGROUND_COLOR);
		TCODConsole::root->setDefaultForeground(DEFAULT_FOREGROUND_COLOR);

		m_playerEntity = m_registry->create();
		Vector2D_t playerStart = { 10, 10 };	// TODO: temporary, will remove later
		m_registry->emplace<PositionComponent>(m_playerEntity, playerStart);
		m_registry->emplace<VelocityComponent>(m_playerEntity);
		m_registry->emplace<RenderComponent>(m_playerEntity, '@', DEFAULT_BACKGROUND_COLOR, TCODColor::green);

		m_currentState = State::STARTUP;

		m_initialized = true;
		return m_initialized;
	}

	bool Engine::Main()
	{
		// verify engine has been intialized otherwise return false
		if (!m_initialized)
		{
			return false;
		}

		m_currentState = State::PLAYING;

		// while window is still open
		while (!TCODConsole::isWindowClosed() && !m_playerWantsToQuit)
		{
			switch (m_currentState)
			{
				case State::PLAYING:

					m_inputHandler->HandlePlayerInput(m_registry, m_playerEntity, m_currentState);
					// TODO: handle AI here
					m_movementHandler->ProcessMovement(m_registry);
					// TODO: change this to just calling the renderer, and call a window/GUI wrapper
					// essentially the window and GUI wrappers should do everything that Engine::Render() does now
					// but without calling the renderer, obviously
					if (!Render())
					{
						return false;
					}

					break;

				case State::QUIT:
					m_playerWantsToQuit = true;
					break;					
			}
		}
		return true;
	}

	bool Engine::Render()
	{
		if (!TCODConsole::root)
		{
			return false;
		}

		TCODConsole::root->clear();

		// show GUI. This will eventually be it's own warpper class
		{
			// print border around world
			TCODConsole::root->putChar(0, 0, TCOD_CHAR_DNW);
			TCODConsole::root->putChar(0, MAP_LOWER_RIGHT_CORNER.y + 1, TCOD_CHAR_DSW);
			TCODConsole::root->putChar(MAP_LOWER_RIGHT_CORNER.x + 1, 0, TCOD_CHAR_DNE);
			TCODConsole::root->putChar(MAP_LOWER_RIGHT_CORNER.x + 1, MAP_LOWER_RIGHT_CORNER.y + 1, TCOD_CHAR_DSE);

			for (int col = 1; col <= MAP_LOWER_RIGHT_CORNER.x; ++col)
			{
				TCODConsole::root->putChar(col, 0, TCOD_CHAR_DHLINE);
				TCODConsole::root->putChar(col, MAP_LOWER_RIGHT_CORNER.y + 1, TCOD_CHAR_DHLINE);
			}

			for (int row = 1; row <= MAP_LOWER_RIGHT_CORNER.y; ++row)
			{
				TCODConsole::root->putChar(0, row, TCOD_CHAR_DVLINE);
				TCODConsole::root->putChar(MAP_LOWER_RIGHT_CORNER.x + 1, row, TCOD_CHAR_DVLINE);
			}

			// print FPS
			TCODConsole::root->printf(69, 48, std::to_string(TCODSystem::getFps()).c_str());

			// build string for current s/w version
			std::string versionString = "v " + std::to_string(VERSION_MAJOR)
				+ "." + std::to_string(VERSION_MINOR)
				+ "." + std::to_string(VERSION_BUILD);

			// print current s/w version
			TCODConsole::root->printf(69, 49, versionString.c_str());
		}

		// render world and all actors
		m_renderer->RenderAll(m_registry);

		TCODConsole::root->flush();

		return true;
	}
}