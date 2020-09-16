/*
ASCII Dungeon

A simple dungeon crawler written in libtcod.

Written by Kevin Garner. kg.dev@protonmail.com
Code repo located at: https://github.com/KevDev13/ASCII_Dungeon
*/

#include "Engine.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // DEBUG

const int WINDOW_SIZE_WIDTH = 80;
const int WINDOW_SIZE_HEIGHT = 50;
const std::string WINDOW_TITLE = "ASCII Dungeon";
const bool WINDOW_START_FULLSCREEN = false;
const int MAXIMUM_FRAMES_PER_SECOND = 60;

int main()
{
	std::unique_ptr<kage::Engine> engine = std::make_unique<kage::Engine>();

	try
	{
		engine->SetInitialWindowProperties(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, WINDOW_TITLE, WINDOW_START_FULLSCREEN, MAXIMUM_FRAMES_PER_SECOND);
	}
	catch (kage::GageException& e)
	{
	#ifdef _DEBUG
		std::cout << e.what();
	#endif // _DEBUG
	}

	// initialize engine and if it fails, exit
	try
	{
		engine->Initialize();
	}
	catch (kage::GageException& e)
	{
	#ifdef _DEBUG
		std::cout << e.what();
	#endif // _DEBUG
	}

	try
	{
		engine->Main();
	}
	catch (kage::GageException& e)
	{
	#ifdef _DEBUG
		std::cout << e.what();
	#endif // _DEBUG
	}
	return 0;
}