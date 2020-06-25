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

		m_player = std::make_unique<Actor>();

		m_rootConsole = nullptr;
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::Initialize()
	{
		// init the window using SDL2
		TCODConsole::initRoot(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, TCOD_RENDERER_SDL2);

		// get pointer to root console
		m_rootConsole = TCODConsole::root;

		// temporary init for Player here
		m_player->SetPosition(Position_t{ 10, 10 });
		m_player->SetDisplayCharacter(PLAYER_DISPLAY_CHAR);

		// set default colors
		m_rootConsole->setDefaultBackground(DEFAULT_BACKGROUND_COLOR);
		m_rootConsole->setDefaultForeground(DEFAULT_FOREGROUND_COLOR);

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
			if (!Render())
			{
				return false;
			}
		}

		return true;
	}

	bool Engine::Render()
	{
		if (!m_rootConsole)
		{
			return false;
		}

		m_rootConsole->clear();
		// eventually here we'll have all the Render functions
		if (!m_player->Render(m_rootConsole))
		{
			return false;
		}

		m_rootConsole->flush();

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