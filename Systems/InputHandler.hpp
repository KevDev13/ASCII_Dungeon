/*
Handles player input

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>

#include "libtcod/libtcod.hpp"
#include "entt/entt.hpp"
#include "State.hpp"

namespace kage
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();

		void HandlePlayerInput(std::shared_ptr<entt::registry> reg, entt::entity player, entt::entity mouse, State& currentState) const;

	protected:
		// keyboard inputs
		char moveUp;
		char moveDown;
		char moveLeft;
		char moveRight;

		char inventory;
		
		const TCOD_keycode_t exitGame = TCOD_keycode_t::TCODK_ESCAPE;
	};
}