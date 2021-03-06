/*
Custom exception class for use in KAGE.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "KageException.hpp"

#include <sstream>

namespace kage
{
	KageException::KageException(int line, std::string file, std::string error)
		: m_line(line), m_file(file), m_error(error)
	{

	}

	const char* KageException::what() const
	{
		std::ostringstream ret;
		ret << "KAGE Exception: " << m_error << std::endl;
		m_buffer = ret.str();
		return m_buffer.c_str();
	}
}