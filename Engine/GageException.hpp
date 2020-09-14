/*
Custom exception class for use in GAGE.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <exception>
#include <string>

namespace gage
{
	class GageException : public std::exception
	{
	public:
		GageException(int line, std::string file);
		std::string GetInfo() const;
		std::string GetType() const { return "GAGE Exception"; }
		int GetLine() const { return m_line; }
		const std::string& GetFile() const { return m_file; }

	protected:
		int m_line;
		std::string m_file;
	};
}