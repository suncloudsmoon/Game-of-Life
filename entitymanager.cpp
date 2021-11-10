#include <memory>
#include <tuple>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"
#include "rules.hpp"

#ifdef DEBUG
#include <iostream>
#endif

namespace gol {
	EntityManager::EntityManager(unsigned int squareSize, unsigned int modeWidth, unsigned int modeHeight,
		int xOffsetSize, int yOffsetSize)
		: blockSize(squareSize), width(modeWidth / blockSize), height(modeHeight / blockSize),
		xOffset(xOffsetSize), yOffset(yOffsetSize)
	{
		isPlayingMotion = false; // the game is paused at first
		generationNum = 0;
		populationCount = 0;
		grid = std::make_unique<Grid<std::unique_ptr<Entity>>>(width, height);
	}

	void EntityManager::initializeEntities() {
		for (unsigned int row = 0; row < width; row++) {
			for (unsigned int col = 0; col < height; col++) {
				grid->at(row, col) = std::make_unique<Entity>(
					toNormalCoordX(row, xOffset, blockSize), toNormalCoordY(col, yOffset, blockSize),
					static_cast<float>(blockSize));
			}
		}
	}

	void EntityManager::updateEntities(const sf::Time& deltaTime) {
		static float elapsedTime = 0;
		if (isPlayingMotion && elapsedTime >= ENTITY_UPDATE_INTERVAL) {
			populationCount = applyGameofLifeRules(grid, gridChangeQueue);
#ifdef DEBUG
			std::cout << "[updateEntities] Population count: " << populationCount << std::endl;
#endif
			while (!gridChangeQueue.empty()) {
				const auto& ele = gridChangeQueue.front();
				grid->at(std::get<0>(ele), std::get<1>(ele))->changeColor(std::get<2>(ele));
				gridChangeQueue.pop();
			}
			generationNum++;
			elapsedTime = 0;
		}
		else {
			elapsedTime += deltaTime.asSeconds();
		}
	}

	void EntityManager::renderEntities(std::unique_ptr<sf::RenderWindow>& window) {
		for (const auto& ptr : grid->getRawArr()) {
			window->draw(*ptr);
		}
	}

	// Getters
	std::unique_ptr<Grid<std::unique_ptr<Entity>>>& EntityManager::getGrid() {
		return grid;
	}

	bool EntityManager::isPlaying() const {
		return isPlayingMotion;
	}

	// Setters
	void EntityManager::setIsPlaying(bool isRunning) {
		isPlayingMotion = isRunning;
	}
}