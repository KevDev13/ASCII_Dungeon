/*
Renderer class, used to render all objects in the game world.
Not used for GUI.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include <algorithm>

#include "Renderer.hpp"

namespace AsciiDungeon
{
	Renderer::Renderer()
	{

	}

	bool Renderer::RenderActors() const
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

	bool Renderer::RenderGUI() const
	{
		return true;
	}

	bool Renderer::RenderWorld() const
	{
		return true;
	}

	bool Renderer::RenderAll() const
	{
		return RenderGUI() && RenderWorld() && RenderActors();
	}

	bool Renderer::AddActor(std::shared_ptr<Actor> actor)
	{
		m_actors.push_back(actor);

		return true;
	}

	bool Renderer::RemoveActor(std::shared_ptr<Actor> actor)
	{
		m_actors.remove(actor);

		return std::find(m_actors.begin(), m_actors.end(), actor) == m_actors.end();
	}

	bool Renderer::RemoveAll()
	{
		m_actors.clear();

		return m_actors.size() == 0;
	}

	Renderer::~Renderer()
	{

	}
}