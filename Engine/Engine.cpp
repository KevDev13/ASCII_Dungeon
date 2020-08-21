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
#include "MouseStatus.hpp"

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
		TCODConsole::setCustomFont(m_gui->GetDefaultFontFile().c_str());

		// init the window using SDL2
		TCODConsole::initRoot(m_windowWidth, m_windowHeight, m_windowTitle.c_str(), m_windowFullscreen, TCOD_RENDERER_SDL2);

		// don't show the cursor
		TCODMouse::showCursor(false);

		// set maximum FPS
		TCODSystem::setFps(m_maxFps);

		// set default colors
		const auto [defaultBackColor, defaultForeColor] = m_gui->GetDefaultColors();
		TCODConsole::root->setDefaultBackground(defaultBackColor);
		TCODConsole::root->setDefaultForeground(defaultForeColor);

		// initialize player entity
		m_playerEntity = m_registry->create();
		Vector2D_t playerStart = { 10, 10 };	// TODO: temporary, will remove later
		m_registry->emplace<PositionComponent>(m_playerEntity, playerStart);
		m_registry->emplace<VelocityComponent>(m_playerEntity);
		m_registry->emplace<RenderComponent>(m_playerEntity, PLAYER_DISPLAY_CHAR, defaultBackColor, TCODColor::green);

		// add mouse component
		m_mouseEntity = m_registry->create();
		m_registry->emplace<MouseStatus>(m_mouseEntity);

		// initial state = startup
		m_currentState = State::STARTUP;

		// set variable to indicate that engine as been initialized and return true
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
			// TODO: move TCODConsole::root->clear() to here? with flush at the end of this while loop
			switch (m_currentState)
			{
				case State::PLAYING:

					// TODO: have a method that will process entities & systems? might be easier, so can only call it if needed
					m_inputHandler->HandlePlayerInput(m_registry, m_playerEntity, m_mouseEntity, m_currentState);
					// TODO: handle AI here
					m_movementHandler->ProcessMovement(m_registry);
					// TODO: change this so that Render() will render appropriately depening on what state we're in
					// i.e. in Main Menu, will display the menu, etc
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
		
		// first, get coordinates for rectangle around map
		Vector2D_t upperLeft = MAP_UPPER_LEFT_CORNER;
		upperLeft.x -= 1;
		upperLeft.y -= 1;
		Vector2D_t lowerRight = MAP_LOWER_RIGHT_CORNER;
		lowerRight.x += 1;
		lowerRight.y += 1;
		m_gui->DrawRectangle(upperLeft, lowerRight, false);
		// display FPS
		m_gui->DisplayText(Vector2D_t(69, 48), "FPS: " + std::to_string(TCODSystem::getFps()));
		// display version info
		m_gui->DisplayText(Vector2D_t(69, 49), BuildVerionString());

		// draw game name & author credit
		m_gui->DisplayText(Vector2D_t(60, 0), "ASCII Dungeon");
		m_gui->DisplayText(Vector2D_t(59, 1), "by Kevin Garner");

		// render world and all actors
		m_renderer->RenderAll(m_registry);

		// handle mouse. Do this last so the mouse cursor will not get covered by anything else (i.e. world, actors, etc)
		if (TCODConsole::root->hasMouseFocus())
		{
			// get current mouse status
			auto mouse = TCODMouse::getStatus();
			Vector2D_t mousePosition = { mouse.cx, mouse.cy };	// use this as the current mouse position

			// move custom mouse cursor
			TCODConsole::root->setCharBackground(mousePosition.x, mousePosition.y, TCODColor::yellow);

			// get mouse info
			auto& mouseStatus = m_registry->get<MouseStatus>(m_mouseEntity);
			Vector2D_t mousePosWhenClicked = mouseStatus.position;	// this is only used for info on where the mouse was when user clicked the mouse button

			// TODO: this is just a demo, eventually update to show info for any actor/anything else in the world
			Vector2D_t playerPosition = m_registry->get<PositionComponent>(m_playerEntity).position;
			if (playerPosition == mousePosition)
			{
				m_gui->DisplayText(Vector2D_t(10, 49), "This is you");
			}

			// if mouse was clicked and mouse was over player. TODO: update this to check for anything clickable
			if (mouseStatus.clicked && mousePosWhenClicked == playerPosition)
			{
				m_gui->DisplayText(Vector2D_t(10, 48), "You clicked yourself!");
				mouseStatus.clicked = false;	// just to be sure we don't get false positives
			}
		}

		TCODConsole::root->flush();

		return true;
	}

	std::string Engine::BuildVerionString()
	{
		return "v " + std::to_string(VERSION_MAJOR)
			+ "." + std::to_string(VERSION_MINOR)
			+ "." + std::to_string(VERSION_BUILD);
	}
}