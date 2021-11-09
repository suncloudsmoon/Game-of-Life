#include "debugmode.hpp"
#include "gameoflife.hpp"

#ifdef DEBUG
#include <iostream>
#endif

int main() {
	GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}

