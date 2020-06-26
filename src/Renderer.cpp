/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Renderer.hpp"

namespace AsciiDungeon
{
	Renderer::Renderer()
	{

	}

	bool Renderer::RenderAll() const
	{
		for (auto actor = m_actors.begin(); actor != m_actors.end(); ++actor)
		{
			TCODConsole::root->setChar(
				(*actor)->GetPosition().x,
				(*actor)->GetPosition().y,
				(*actor)->GetDisplayCharacter());
		}

		return true;
	}

	bool Renderer::AddActor(std::shared_ptr<Actor> actor)
	{
		m_actors.push_back(actor);

		return true;
	}

	Renderer::~Renderer()
	{

	}
}