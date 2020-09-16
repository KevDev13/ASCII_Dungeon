/*
GUI class

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include "libtcod/libtcod.hpp"
#include "Vector2D.hpp"

namespace kage
{
	class GUI
	{
	public:
		GUI();
		~GUI();

		void DrawRectangle(Vector2D_t upperLeft, Vector2D_t lowerRight, bool singleLine = true) const;
		void DisplayText(Vector2D_t startPoint, std::string text) const;

		// used to get default colors
		// TODO: eventually make this settable from Engine, and just have the constants here be the "default" default
		inline TCODColor GetDefaultBackgroundColor() const { return DEFAULT_BACKGROUND_COLOR; }
		inline TCODColor GetDefaultForegroundColor() const { return DEFAULT_FOREGROUND_COLOR; }
		inline std::tuple<TCODColor, TCODColor> GetDefaultColors() const { return { DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR }; }

		inline std::string GetDefaultFontFile() const { return DEFAULT_FONT_FILE; }

	protected:
		static const TCODColor DEFAULT_BACKGROUND_COLOR;
		static const TCODColor DEFAULT_FOREGROUND_COLOR;
		static const std::string DEFAULT_FONT_FILE;
	};
}