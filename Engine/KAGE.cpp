/*
Kevin's ASCII Game Engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "KAGE.hpp"

namespace kage
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
			m_collisionHandler = make_unique<CollisionHandler>();
			m_gui = make_unique<GUI>();
			m_currentMap = make_shared<Map>();
			m_NpcEntities = make_shared<vector<entt::entity>>();
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
	void Engine::Initialize(int w, int h, std::string title, bool startFullscreen, int maxFps)
	{
		// check for bad conditions
		if (h <= 0 || w <= 0 || maxFps <= 30)
		{
			KAGE_EXCEPTION("Initial window properties invalid.");
			return;
		}

		m_windowWidth = w;
		m_windowHeight = h;
		m_windowTitle = title;
		m_windowFullscreen = startFullscreen;
		m_maxFps = maxFps;

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

		// set render space for Renderer
		m_renderer->SetRenderSpace(MAP_TOP_LEFT_CORNER, MAP_BOTTOM_RIGHT_CORNER);

		// initialize player entity
		m_playerEntity = m_registry->create();
		Vector2D_t playerStart = { 10, 10 };	// TODO: temporary, will remove later
		m_registry->emplace<PositionComponent>(m_playerEntity, playerStart);
		m_registry->emplace<VelocityComponent>(m_playerEntity);
		m_registry->emplace<RenderComponent>(m_playerEntity, PLAYER_DISPLAY_CHAR, defaultBackColor, PLAYER_FORE_COLOR);
		m_registry->emplace<DisplayInfo>(m_playerEntity, "Player");

		// initialize test NPC
		entt::entity npc = CreateNPC({ 5, 5 }, 2, defaultBackColor, defaultForeColor);

		// add mouse component
		m_mouseEntity = m_registry->create();
		m_registry->emplace<MouseStatus>(m_mouseEntity);

		// initial state = startup
		m_currentState = State::STARTUP;

		// set variable to indicate that engine as been initialized and return true
		m_initialized = true;
	}

	void Engine::Main()
	{
		// verify engine has been intialized otherwise return false
		if (!m_initialized)
		{
			KAGE_EXCEPTION("Engine not initialized.");
			return;
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
					m_collisionHandler->DetectCollisions(m_registry);
					// TODO: any other detection for valid movement should be done before the next line (ProcessMovement)
					m_movementHandler->ProcessMovement(m_registry);
					// TODO: change this so that Render() will render appropriately depening on what state we're in
					// i.e. in Main Menu, will display the menu, etc
					if (!Render())
					{
						KAGE_EXCEPTION("Render error.");
						return;
					}

					break;					
			}
		}
	}

	entt::entity Engine::CreateNPC(Vector2D_t pos, const char displayChar, const TCODColor backColor, const TCODColor foreColor)
	{
		entt::entity npc = m_registry->create();
		// add all NPC components here
		m_registry->emplace<PositionComponent>(npc, pos);
		m_registry->emplace<VelocityComponent>(npc);
		m_registry->emplace<RenderComponent>(npc, displayChar, backColor, foreColor);
		m_registry->emplace<Collider>(npc);
		m_registry->emplace<DisplayInfo>(npc, "Test NPC");
		// TODO: add AI component;

		// add NPC to NPC entity list
		m_NpcEntities->push_back(npc);

		return npc;
	}

	bool Engine::Render()
	{
		if (!TCODConsole::root)
		{
			KAGE_EXCEPTION("TCOD Console Root not found.");
			return false;
		}

		TCODConsole::root->clear();

		// draw GUI components
		
		// first, get coordinates for rectangle around map
		Vector2D_t upperLeft = MAP_TOP_LEFT_CORNER;
		upperLeft -= {1, 1};
		Vector2D_t lowerRight = MAP_BOTTOM_RIGHT_CORNER;
		lowerRight += {1, 1};

		m_gui->DrawRectangle(upperLeft, lowerRight, false);

		// this is temporary, but display player position in world space
		// TODO: remove this
		Vector2D_t playerPos = m_registry->get<PositionComponent>(m_playerEntity).position;
		m_gui->DisplayText(Vector2D_t(69, 47), std::to_string(playerPos.x) + ", " + std::to_string(playerPos.y));

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

			Vector2D_t playerPosition = m_registry->get<PositionComponent>(m_playerEntity).position;

			// display the text for whatever the mouse is hovering over
			auto displayComponents = m_registry->view<PositionComponent, DisplayInfo>();
			for (auto entity : displayComponents)
			{
				const auto [pos, dispName] = m_registry->get<PositionComponent, DisplayInfo>(entity);
				if (pos.position == mousePosition)
				{
					m_gui->DisplayText(Vector2D_t(10, 49), dispName.name);
				}
			}

			// if mouse was clicked and mouse was over player. 
			// TODO: update this to check for anything clickable
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
		return "v " + std::to_string(GAGE_VERSION_MAJOR)
			+ "." + std::to_string(GAGE_VERSION_MINOR)
			+ "." + std::to_string(GAGE_VERSION_PATCH);
	}
}