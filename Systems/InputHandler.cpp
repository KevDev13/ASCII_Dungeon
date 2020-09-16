/*
Handles player input

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "InputHandler.hpp"
#include "VelocityComponent.hpp"
#include "MouseStatus.hpp"

namespace kage
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

	void InputHandler::HandlePlayerInput(std::shared_ptr<entt::registry> reg, entt::entity player, entt::entity mouse, State& currentState) const
	{
		// player velocity
		auto& playerVelocity = reg->get<VelocityComponent>(player);

		// mouse status
		auto& mouseStatus = reg->get<MouseStatus>(mouse);

		// key for input
		TCOD_key_t key;
		// mouse input
		TCOD_mouse_t mouseEvent;
		TCOD_event_t ev = TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE_PRESS, &key, &mouseEvent);

		// set position, and reset clicked to false
		mouseStatus.position = { mouseEvent.cx, mouseEvent.cy };
		mouseStatus.clicked = false;
		
		// handle keyboard input
		if (ev == TCOD_EVENT_KEY_PRESS)
		{
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
					else if (input == moveDown)
					{
						playerVelocity = { 0, 1 };
					}
					else if (input == moveLeft)
					{
						playerVelocity = { -1, 0 };
					}
					else if (input == moveRight)
					{
						playerVelocity = { 1, 0 };
					}
					else
					{

					}

					if (input == inventory)
					{

					}
				}
				break;

				// player wants to quit
				case TCODK_ESCAPE:
					currentState = State::QUIT;
					break;

				default:
					break;
			}
		}
		else if (ev == TCOD_EVENT_MOUSE_PRESS && mouseEvent.lbutton)
		{
			mouseStatus.clicked = true;
		}
	}
}