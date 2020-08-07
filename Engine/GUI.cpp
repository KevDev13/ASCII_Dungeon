/*
GUI class

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "GUI.hpp"

namespace gage
{
	GUI::GUI()
	{

	}

	GUI::~GUI()
	{

	}

	void GUI::DrawRectangle(Vector2D_t upperLeft, Vector2D_t lowerRight) const
	{
		// draw corners
		TCODConsole::root->putChar(upperLeft.x, upperLeft.y, TCOD_CHAR_DNW);
		TCODConsole::root->putChar(upperLeft.x, lowerRight.y, TCOD_CHAR_DSW);
		TCODConsole::root->putChar(lowerRight.x, upperLeft.y, TCOD_CHAR_DNE);
		TCODConsole::root->putChar(lowerRight.x, lowerRight.y, TCOD_CHAR_DSE);

		// draw straight lines
		for (int col = upperLeft.x + 1; col < lowerRight.x; ++col)
		{
			TCODConsole::root->putChar(col, upperLeft.y, TCOD_CHAR_DHLINE);
			TCODConsole::root->putChar(col, lowerRight.y, TCOD_CHAR_DHLINE);
		}

		for (int row = upperLeft.y + 1; row < lowerRight.y; ++row)
		{
			TCODConsole::root->putChar(upperLeft.x, row, TCOD_CHAR_DVLINE);
			TCODConsole::root->putChar(lowerRight.x, row, TCOD_CHAR_DVLINE);
		}
	}

	void GUI::DisplayText(Vector2D_t startPoint, std::string text) const
	{
		TCODConsole::root->printf(startPoint.x, startPoint.y, text.c_str());
	}
}