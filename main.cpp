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

#include <stdexcept>
#include <csignal>

#include "debugmode.hpp"
#include "gameoflife.hpp"
#include "errorbox.hpp"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef DEBUG
#include <iostream>
#endif

 /*
 * TODO:
 * - Add license (MIT-0)
 * - Add good logging class, platform-independent warning/error messagebox (using ifdef), and try catch entire program!
 * - Create font
 * - Add text stats under the play/pause button
 * - Add slow/medium/fast mode
 * - Add game home screen w/ play and settings
 * - Add readme
 * - Share project
 */

static void handleSignalErrors(int signal) {
	switch (signal) {
	case SIGSEGV:
		util::displayErrorBox("Fault", "Segmentation Error at unknown location!");
		break;
	default:
		break;
	}
}

#if !defined DEBUG
#ifdef _WIN32
int CALLBACK WinMain(HINSTANCE inst1, HINSTANCE inst2, LPSTR line, int n)
#else
int main()
#endif
{
	// "Catch" Signal Errors
	if (std::signal(SIGSEGV, handleSignalErrors) == SIG_ERR) {
		util::displayErrorBox("Runtime Error", "Unable to initialize signal handler!");
	}
	try {
		gol::GameOfLife game("Game of Life", 1920, 1080, false);
		game.start();
	}
	catch (std::exception& e) {
		util::displayErrorBox("Runtime Error", e.what());
	}
}
#else
int main()
{
	gol::GameOfLife game("Game of Life", 1920, 1080, false);
	game.start();
}
#endif
