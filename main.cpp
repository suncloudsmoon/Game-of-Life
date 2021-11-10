/*
 * Copyright (c) 2021, suncloudsmoon and the Game-of-Life contributors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

