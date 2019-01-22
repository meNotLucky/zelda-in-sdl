#pragma once
#include <iostream>
#include <SDL.h>

class ErrorLogger {
public:
	void log_error(std::string sdl_lib, const char* error_type) {
		std::string error_string = "Couldn't initialize SDL" + sdl_lib + ": %s";
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, error_string.c_str(), error_type);
		return;
	}
};