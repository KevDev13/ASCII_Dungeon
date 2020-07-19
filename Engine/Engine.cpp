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
		}
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::Initialize()
	{
		TCODConsole::setCustomFont(FONT_FILE);

		// init the window using SDL2
		TCODConsole::initRoot(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, TCOD_RENDERER_SDL2);

		// set default colors
		TCODConsole::root->setDefaultBackground(DEFAULT_BACKGROUND_COLOR);
		TCODConsole::root->setDefaultForeground(DEFAULT_FOREGROUND_COLOR);

		m_playerEntity = m_registry->create();
		Vector2D_t playerStart = { 10, 10 };
		m_registry->emplace<PositionComponent>(m_playerEntity, playerStart);
		m_registry->emplace<RenderComponent>(m_playerEntity, '@', DEFAULT_BACKGROUND_COLOR, TCODColor::green);

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

		// while window is still open
		while (!TCODConsole::isWindowClosed() && !m_playerWantsToQuit)
		{
			m_inputHandler->HandlePlayerInput(m_registry, m_playerEntity);
			// eventually, NPC AI will be run here
			if (!Render())
			{
				return false;
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

		// show GUI. This will eventually be it's own class
		{
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

			std::string versionString = "v " + std::to_string(VERSION_MAJOR)
				+ "." + std::to_string(VERSION_MINOR)
				+ "." + std::to_string(VERSION_BUILD);

			TCODConsole::root->printf(69, 49, versionString.c_str());
		}

		// render world and all actors
		m_renderer->RenderAll(m_registry);

		TCODConsole::root->flush();

		return true;
	}
}