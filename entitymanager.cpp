#include <memory>
#include <cmath>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"

#ifdef DEBUG
#include <iostream>
#endif

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
		populationCount = applyGameofLifeRules();
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
/*
* Rules of the game:
* If is living
* 1) neighbours < 2 ==> dies
* 2) neighbours > 3 ==> dies
* 
* If is dead
* 1) neighbours == 3 ==> gets to be alive
*/
unsigned int EntityManager::applyGameofLifeRules() {
	unsigned int numLiving = 0;
	for (unsigned int row = 0; row < width; row++) {
		for (unsigned int col = 0; col < height; col++) {
			bool isLiving = !getGridEntityStateAt(row, col);
			unsigned int numNeighbours = getNumNeighbours(row, col);

			if (isLiving && (numNeighbours < 2 || numNeighbours > 3)) {
				// true = white, false = black
				gridChangeQueue.push(std::tuple<unsigned int, unsigned int, bool>(row, col, true));
			}
			else if (!isLiving && numNeighbours == 3) {
				gridChangeQueue.push(std::tuple<unsigned int, unsigned int, bool>(row, col, false));
			}
			numLiving += isLiving;
		}
	}
	while (!gridChangeQueue.empty()) {
		const auto& ele = gridChangeQueue.front();
		setGridEntityAt(std::get<0>(ele), std::get<1>(ele), std::get<2>(ele));
		gridChangeQueue.pop();
	}
	return numLiving;
}

/*
* Grid Example:
* - - -
* - - -
* - - -
*/
unsigned int EntityManager::getNumNeighbours(int x, int y) {
	unsigned int numNeighbours = 0;
	// Left
	if (x - 1 >= 0) {
		if (y - 1 >= 0)
			numNeighbours += !getGridEntityStateAt(x - 1, y - 1);
		if (y + 1 < static_cast<int>(height))
			numNeighbours += !getGridEntityStateAt(x - 1, y + 1);
		numNeighbours += !getGridEntityStateAt(x - 1, y);
	}
	// Center
	if (y - 1 >= 0)
		numNeighbours += !getGridEntityStateAt(x, y - 1);
	if (y + 1 < static_cast<int>(height))
		numNeighbours += !getGridEntityStateAt(x, y + 1);

	// Right
	if (x + 1 < static_cast<int>(width)) {
		if (y - 1 >= 0)
			numNeighbours += !getGridEntityStateAt(x + 1, y - 1);
		if (y + 1 < static_cast<int>(height))
			numNeighbours += !getGridEntityStateAt(x + 1, y + 1);
		numNeighbours += !getGridEntityStateAt(x + 1, y);
	}
	return numNeighbours;
}

// Getters and Setters
void EntityManager::setIsPlaying(bool isRunning) {
	isPlayingMotion = isRunning;
}

bool EntityManager::isPlaying() const {
	return isPlayingMotion;
}