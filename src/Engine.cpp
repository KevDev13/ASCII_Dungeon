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

	Engine::Engine()
	{
		m_initialized = false;
		m_playerWantsToQuit = false;
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::Initialize()
	{
		// init the window using SDL2
		TCODConsole::initRoot(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, TCOD_RENDERER_SDL2);

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
			Render();
		}

		return true;
	}

	void Engine::Render()
	{
		TCODConsole::root->clear();

		const char p = '@';	// temp variable for character, just to display something for now
		TCODConsole::root->putChar(10, 10, p);

		TCODConsole::root->flush();
	}

	void Engine::HandleInput()
	{
		TCOD_key_t key;
		TCOD_mouse_t mouse;
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);

		// handle keyboard input here

		// handle mouse input here
	}
}