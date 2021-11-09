#include "debugmode.hpp"
#include "gameoflife.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#ifndef DEBUG
#ifdef _WIN32
int WinMain() {
	GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}
#endif
#else
int main() {
	GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}
#endif

