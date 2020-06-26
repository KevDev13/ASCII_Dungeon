/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <memory>
#include <list>

#include "libtcod.h"
#include "Actor.hpp"

namespace AsciiDungeon
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		bool RenderAll() const;

		bool AddActor(std::shared_ptr <Actor> actor);
		bool RemoveActor(std::shared_ptr<Actor> actor);
		bool RemoveAll();

	protected:
		std::list<std::shared_ptr<Actor>> m_actors;
	};

}