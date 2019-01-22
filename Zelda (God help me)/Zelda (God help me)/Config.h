#pragma once
	
enum flag {
	FULLSCREEN,
	BORDERLESS,
	WINDOWED
};

struct Config {

	static const int SCREEN_WIDTH = 1024;
	static const int SCREEN_HEIGHT = 960;
	static const flag SCREENMODE = WINDOWED;
};