#ifndef RULES_HPP
#define RULES_HPP

#include <memory>
#include <queue>

#include "grid.hpp"
#include "entity.hpp"

namespace gol {
	unsigned int applyGameofLifeRules(std::unique_ptr<Grid<std::unique_ptr<Entity>>>& grid,
		std::queue<std::tuple<unsigned int, unsigned int, bool>>& queue);
	unsigned int getNumNeighbours(const std::unique_ptr<Grid<std::unique_ptr<Entity>>>& grid, int x, int y);
}

#endif /* RULES_HPP */