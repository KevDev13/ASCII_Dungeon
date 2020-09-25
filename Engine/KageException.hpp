/*
Custom exception class for use in GAGE.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#pragma once

#include <exception>
#include <string>

namespace kage
{
	class KageException : public std::exception
	{
	public:
		KageException(int line, std::string file, std::string error);
		const char* what() const override;
		std::string GetType() const { return "KAGE Exception"; }
		int GetLine() const { return m_line; }
		const std::string& GetFile() const { return m_file; }

	protected:
		int m_line;
		std::string m_file;
		std::string m_error;
		mutable std::string m_buffer;
	};

#define KAGE_EXCEPTION(err) throw KageException(__LINE__, __FILE__, err)
}