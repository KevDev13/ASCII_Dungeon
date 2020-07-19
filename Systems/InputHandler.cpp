/*
Handles player input

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "InputHandler.hpp"
#include "VelocityComponent.hpp"

namespace asciidungeon
{
	InputHandler::InputHandler()
	{
		moveUp = 'w';
		moveDown = 's';
		moveLeft = 'a';
		moveRight = 'd';

		inventory = 'i';
	}

	InputHandler::~InputHandler() {}

	void InputHandler::HandlePlayerInput(std::shared_ptr<entt::registry> reg, entt::entity& player) const
	{
		// player velocity
		auto& playerVelocity = reg->get<VelocityComponent>(player);

		// key for input
		TCOD_key_t key;
		//TCOD_mouse_t mouse;
		//TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, &mouse);
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

		switch (key.vk)
		{
			// if a character was pressed
			case TCODK_CHAR:
			{ // using braces here to avoid error of declaring char input within a case statement. Only need the variable in this case anyway.
				char input = key.c;

				// have to use nexted if else statements instead of a switch statement since C++ can't use variables in switch statements
				// if we remove the ability to remap keyboard inputs and make these all constants, can go back to a switch statement
				if (input == moveUp)
				{
					playerVelocity = { 0, -1 };
				}
				else if (input = moveDown)
				{
					playerVelocity = { 0, 1 };
				}
				else if (input = moveLeft)
				{
					playerVelocity = { -1, 0 };
				}
				else if (input = moveRight)
				{
					playerVelocity = { 1, 0 };
				}
				else
				{
					// set velocity to 0 since player doesn't want to move
					playerVelocity = { 0, 0 };
				}
				
				if (input = inventory)
				{

				}
			}

			break;

			// player wants to quit
			case TCODK_ESCAPE:
				//m_playerWantsToQuit = true;
				break;

			default:
				break;
		}
	}
}