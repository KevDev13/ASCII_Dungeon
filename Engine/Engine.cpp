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

namespace gage
{
	Engine::Engine()
	{
		m_initialized = false;

		{
			using namespace std;
			m_registry = make_shared<entt::registry>();
			m_renderer = make_unique<Renderer>();
			m_inputHandler = make_unique<InputHandler>();
			m_movementHandler = make_unique<MovementHandler>();
			m_gui = make_unique<GUI>();
		}

		m_windowWidth = 0;
		m_windowHeight = 0;
		m_windowTitle = "";
		m_windowFullscreen = false;
		m_maxFps = 0;
	}

	Engine::~Engine()
	{
		TCOD_quit();
	}

	bool Engine::SetInitialWindowProperties(int w, int h, std::string title, bool startFullscreen, int maxFps)
	{
		// check for bad conditions
		if (h <= 0 || w <= 0 || maxFps <= 30)
		{
			return false;
		}

		m_windowWidth = w;
		m_windowHeight = h;
		m_windowTitle = title;
		m_windowFullscreen = startFullscreen;
		m_maxFps = maxFps;

		return true;
	}

	bool Engine::Initialize()
	{
		// if window width is 0, that means SetInitialWindowProperties hasn't been called yet, so return false
		if (m_windowWidth == 0)
		{
			return false;
		}

		// setup font file
		TCODConsole::setCustomFont(FONT_FILE);

		// init the window using SDL2
		TCODConsole::initRoot(m_windowWidth, m_windowHeight, m_windowTitle.c_str(), m_windowFullscreen, TCOD_RENDERER_SDL2);

		// set maximum FPS
		TCODSystem::setFps(m_maxFps);

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
		while (!TCODConsole::isWindowClosed() && m_currentState != State::QUIT)
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

		// draw GUI components
		Vector2D_t upperLeft = MAP_UPPER_LEFT_CORNER;
		upperLeft.x -= 1;
		upperLeft.y -= 1;
		Vector2D_t lowerRight = MAP_LOWER_RIGHT_CORNER;
		lowerRight.x += 1;
		lowerRight.y += 1;
		m_gui->DrawRectangle(upperLeft, lowerRight);
		m_gui->DisplayFPS(Vector2D_t(69, 48));
		m_gui->DisplayVersionInfo(Vector2D_t(69, 49), VERSION_MAJOR, VERSION_MINOR, VERSION_BUILD);

		// render world and all actors
		m_renderer->RenderAll(m_registry);

		TCODConsole::root->flush();

		return true;
	}
}