/*
Main game engine

Written by Kevin Garner. kg.dev@protonmail.com

Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

namespace AsciiDungeon
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Initialize();
		bool Main();

	protected:
		bool m_initialized;
	};

}
