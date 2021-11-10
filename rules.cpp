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

#include <queue>
#include <memory>

#include "rules.hpp"
#include "grid.hpp"

namespace gol {
	/*
	* Rules of the game:
	* If is living
	* 1) neighbours < 2 ==> dies
	* 2) neighbours > 3 ==> dies
	*
	* If is dead
	* 1) neighbours == 3 ==> gets to be alive
	*/
	unsigned int applyGameofLifeRules(std::unique_ptr<Grid<std::unique_ptr<Entity>>>& grid,
		std::queue<std::tuple<unsigned int, unsigned int, bool>>& queue) {
		unsigned int numLiving = 0;
		for (size_t row = 0; row < grid->getWidth(); row++) {
			for (size_t col = 0; col < grid->getHeight(); col++) {
				bool isLiving = !grid->at(row, col)->isWhite();
				unsigned int numNeighbours = getNumNeighbours(grid, row, col);

				if (isLiving && (numNeighbours < 2 || numNeighbours > 3)) {
					// true = white, false = black
					queue.push(std::tuple<unsigned int, unsigned int, bool>(row, col, true));
				}
				else if (!isLiving && numNeighbours == 3) {
					queue.push(std::tuple<unsigned int, unsigned int, bool>(row, col, false));
				}
				numLiving += isLiving;
			}
		}
		return numLiving;
	}

	/*
	* Grid Example:
	* - - -
	* - - -
	* - - -
	*/
	unsigned int getNumNeighbours(const std::unique_ptr<Grid<std::unique_ptr<Entity>>>& grid, int x, int y) {
		unsigned int numNeighbours = 0;
		// Left
		if (x - 1 >= 0) {
			if (y - 1 >= 0)
				numNeighbours += !grid->at(x - 1, y - 1)->isWhite();
			if (y + 1 < static_cast<int>(grid->getHeight()))
				numNeighbours += !grid->at(x - 1, y + 1)->isWhite();
			numNeighbours += !grid->at(x - 1, y)->isWhite();
		}
		// Center
		if (y - 1 >= 0)
			numNeighbours += !grid->at(x, y - 1)->isWhite();
		if (y + 1 < static_cast<int>(grid->getHeight()))
			numNeighbours += !grid->at(x, y + 1)->isWhite();

		// Right
		if (x + 1 < static_cast<int>(grid->getWidth())) {
			if (y - 1 >= 0)
				numNeighbours += !grid->at(x + 1, y - 1)->isWhite();
			if (y + 1 < static_cast<int>(grid->getHeight()))
				numNeighbours += !grid->at(x + 1, y + 1)->isWhite();
			numNeighbours += !grid->at(x + 1, y)->isWhite();
		}
		return numNeighbours;
	}
}
