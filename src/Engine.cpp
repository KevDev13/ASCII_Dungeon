/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Engine.hpp"
#include "libtcod.h"

namespace AsciiDungeon
{
	const int WINDOW_SIZE_HEIGHT = 50;
	const int WINDOW_SIZE_WIDTH = 80;
	const char* WINDOW_TITLE = "ASCII Dungeon";
	const bool WINDOW_START_FULLSCREEN = false;

	const char PLAYER_DISPLAY_CHAR = '@';
	const TCODColor DEFAULT_BACKGROUND_COLOR = TCODColor::black;
	const TCODColor DEFAULT_FOREGROUND_COLOR = TCODColor::yellow;

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
			// player movement (in work)
			case TCODK_UP:
				m_player->MoveUp();
				break;
			case TCODK_DOWN:
				m_player->MoveDown();
				break;
			case TCODK_LEFT:
				m_player->MoveLeft();
				break;
			case TCODK_RIGHT:
				m_player->MoveRight();
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