/*
Custom exception class for use in GAGE.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "GageException.hpp"

namespace gage
{
	GageException::GageException(int line, std::string file)
		: m_line(line), m_file(file)
	{

	}

	std::string GageException::GetInfo() const
	{
		std::string ret = "GAGE Exception on line " + m_line;
		ret += " in file " + m_file;
		return ret;
	}
}