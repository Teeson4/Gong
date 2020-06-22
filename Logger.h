#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>

class Logger
{

public:

	static void info(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (INFO) " << message << std::endl;
	}

	static void warning(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (WARNING) " << message << std::endl;
	}

	static void error(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (ERROR) " << message << std::endl;
	}

	static void errorSDL(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (ERROR) " << message << " SDL Error: " << SDL_GetError() << std::endl;
	}

	static void errorIMG(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (ERROR) " << message << " SDL_image Error: " << IMG_GetError() << std::endl;
	}

	static void errorTTF(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (ERROR) " << message << " SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

	static void errorMIX(const char* tag, const char* message)
	{
		std::cout << "[" << tag << "] (ERROR) " << message << " SDL_Mix Error: " << Mix_GetError() << std::endl;
	}

};

