/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Engine.hpp"
#include "libtcod.h"
#include "Constants.hpp"

namespace AsciiDungeon
{
	Engine::Engine()
	{
		m_initialized = false;
		m_playerWantsToQuit = false;

		m_player = std::make_shared<Actor>();
		m_renderer = std::make_unique<Renderer>();
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::Initialize()
	{
		TCODConsole::setCustomFont("png/bitmap_col.png");

		// init the window using SDL2
		TCODConsole::initRoot(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, TCOD_RENDERER_SDL2);

		// temporary init for Player here
		m_player->SetPosition(Position_t{ 10, 10 });
		m_player->SetDisplayCharacter(PLAYER_DISPLAY_CHAR);

		// set default colors
		TCODConsole::root->setDefaultBackground(DEFAULT_BACKGROUND_COLOR);
		TCODConsole::root->setDefaultForeground(DEFAULT_FOREGROUND_COLOR);

		// add player to Renderer
		m_renderer->AddActor(m_player);

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
			HandleInput();
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
		m_renderer->RenderAll();

		TCODConsole::root->flush();

		return true;
	}

	void Engine::HandleInput()
	{
		TCOD_key_t key;
		//TCOD_mouse_t mouse;
		//TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

		switch (key.vk)
		{
			//case TCODK_UP:
			//	m_player->MoveUp();
			//	break;
			//case TCODK_DOWN:
			//	m_player->MoveDown();
			//	break;
			//case TCODK_LEFT:
			//	m_player->MoveLeft();
			//	break;
			//case TCODK_RIGHT:
			//	m_player->MoveRight();
			//	break;

			// if a character was pressed
			case TCODK_CHAR:
				switch (key.c)
				{
					case PlayerInput::MOVE_UP:
						m_player->MoveUp();
						break;
					case PlayerInput::MOVE_DOWN:
						m_player->MoveDown();
						break;
					case PlayerInput::MOVE_LEFT:
						m_player->MoveLeft();
						break;
					case PlayerInput::MOVE_RIGHT:
						m_player->MoveRight();
						break;
					default:
						break;
				}
				break;

			// player wants to quit
			case TCODK_ESCAPE:
				m_playerWantsToQuit = true;
				break;

			default:
				break;
		}

		// handle mouse input here
	}
}