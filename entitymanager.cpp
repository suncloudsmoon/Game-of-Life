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