/*
RenderComponent structure

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod/libtcod.hpp"

namespace kage
{
	//extern const TCODColor DEFAULT_BACKGROUND_COLOR;
	//extern const TCODColor DEFAULT_FOREGROUND_COLOR;

	struct RenderComponent
	{
		TCODColor backgroundColor;
		TCODColor foregroundColor;
		char displayCharacter;

		RenderComponent() = default;
		//RenderComponent(char ch) : backgroundColor(DEFAULT_BACKGROUND_COLOR), foregroundColor(DEFAULT_FOREGROUND_COLOR), displayCharacter(ch) {}
		RenderComponent(char ch, TCODColor bc, TCODColor fc) : backgroundColor(bc), foregroundColor(fc), displayCharacter(ch) {}
	};
}