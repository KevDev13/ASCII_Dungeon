/*
Custom exception class for use in GAGE.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "GageException.hpp"

#include <sstream>

namespace gage
{
	GageException::GageException(int line, std::string file, std::string error)
		: m_line(line), m_file(file), m_error(error)
	{

	}

	const char* GageException::what() const
	{
		std::ostringstream ret;
		ret << "GAGE Exception: " << m_error << std::endl;
		m_buffer = ret.str();
		return m_buffer.c_str();
	}
}