/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "Actor.hpp"

namespace AsciiDungeon
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Main();

		inline bool PlayerWantsToQuit() const { return m_playerWantsToQuit; }

	protected:
		bool m_initialized;
		bool m_playerWantsToQuit;

		std::unique_ptr<Actor> m_player;

		void HandleInput();
		void Render();
	};

}
