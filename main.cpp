#include "debugmode.hpp"
#include "gameoflife.hpp"

#ifdef DEBUG
#include <iostream>
#endif

/*
* TODO:
* - Add license (MIT-0)
* - Create font
* - Add text stats under the play/pause button
* - Add slow/medium/fast mode
* - Add game home screen w/ play and settings
* - Add readme
* - Share project
*/

#if !defined DEBUG && defined _WIN32
int WinMain() {
	GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}
#else
int main() {
	gol::GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}
#endif

