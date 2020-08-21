/*
GUI class

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "GUI.hpp"

namespace gage
{
	// set default colors
	const TCODColor GUI::DEFAULT_BACKGROUND_COLOR = TCODColor::black;
	const TCODColor GUI::DEFAULT_FOREGROUND_COLOR = TCODColor::white;

	// set default font file
	const std::string GUI::DEFAULT_FONT_FILE = "png/bitmap_col.png";

	GUI::GUI()
	{

	}

	GUI::~GUI()
	{

	}

	void GUI::DrawRectangle(Vector2D_t upperLeft, Vector2D_t lowerRight, bool singleLine) const
	{
		// draw corners
		TCODConsole::root->putChar(upperLeft.x, upperLeft.y, singleLine ? TCOD_CHAR_NW : TCOD_CHAR_DNW);
		TCODConsole::root->putChar(upperLeft.x, lowerRight.y, singleLine ? TCOD_CHAR_SW : TCOD_CHAR_DSW);
		TCODConsole::root->putChar(lowerRight.x, upperLeft.y, singleLine ? TCOD_CHAR_NE : TCOD_CHAR_DNE);
		TCODConsole::root->putChar(lowerRight.x, lowerRight.y, singleLine ? TCOD_CHAR_SE : TCOD_CHAR_DSE);

		// draw straight lines
		for (int col = upperLeft.x + 1; col < lowerRight.x; ++col)
		{
			TCODConsole::root->putChar(col, upperLeft.y, singleLine ? TCOD_CHAR_HLINE : TCOD_CHAR_DHLINE);
			TCODConsole::root->putChar(col, lowerRight.y, singleLine ? TCOD_CHAR_HLINE : TCOD_CHAR_DHLINE);
		}

		for (int row = upperLeft.y + 1; row < lowerRight.y; ++row)
		{
			TCODConsole::root->putChar(upperLeft.x, row, singleLine ? TCOD_CHAR_VLINE : TCOD_CHAR_DVLINE);
			TCODConsole::root->putChar(lowerRight.x, row, singleLine ? TCOD_CHAR_VLINE : TCOD_CHAR_DVLINE);
		}
	}

	void GUI::DisplayText(Vector2D_t startPoint, std::string text) const
	{
		TCODConsole::root->printf(startPoint.x, startPoint.y, text.c_str());
	}
}