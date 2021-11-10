
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
