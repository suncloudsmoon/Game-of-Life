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

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <memory>
#include <queue>
#include <tuple>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entity.hpp"
#include "grid.hpp"
#include "coordutil.hpp"

#ifdef DEBUG
#include <iostream>
#endif

namespace gol {
	constexpr float ENTITY_UPDATE_INTERVAL = 0.5f;

	class EntityManager {
	public:
		/*
		* Sets the width and height to (width / blockSize) and (height / blockSize)
		*/
		EntityManager(unsigned int squareSize, unsigned int modeWidth, unsigned int modeHeight,
			int xOffsetSize = 0, int yOffsetSize = 0);
		void initializeEntities(); // white squares with gray border
		void updateEntities(const sf::Time& deltaTime);
		void renderEntities(std::unique_ptr<sf::RenderWindow>& window);

		template<class T>
		bool isWithinGrid(T x, T y) {
			x = toBlockyCoordX(x, xOffset, blockSize);
			y = toBlockyCoordY(y, yOffset, blockSize);
#ifdef DEBUG
			std::cout << "[isWithinGrid] ";
			std::cout << "[" << x << "," << y << "]";
			std::cout << ", Width: " << width;
			std::cout << ", Height: " << height;
			std::cout << ", xOffset: " << xOffset;
			std::cout << ", yOffset: " << yOffset;
			std::cout << std::endl;
#endif
			return (x >= 0 && x < width) && (y >= 0 && y < height);
		}

		// Getters
		std::unique_ptr<Grid<std::unique_ptr<Entity>>>& getGrid();
		bool isPlaying() const;

		template<class T>
		bool getEntityStateAt(T x, T y) {
			return grid->at(toBlockyCoordX(x, xOffset, blockSize), toBlockyCoordY(y, yOffset, blockSize))->isWhite();
		}

		// Setters
		void setIsPlaying(bool isPlayingMotion);

		template<class T>
		void setEntityStateAt(T x, T y, bool isWhite) {
			grid->at(toBlockyCoordX(x, xOffset, blockSize),
				toBlockyCoordY(y, yOffset, blockSize))->changeColor(isWhite);
		}
	private:
		// Block Stats
		unsigned int blockSize, width, height;
		int xOffset, yOffset;

		// Game of Life Stats
		bool isPlayingMotion;
		unsigned int generationNum;
		unsigned int populationCount;

		std::unique_ptr<Grid<std::unique_ptr<Entity>>> grid;
		std::queue<std::tuple<unsigned int, unsigned int, bool>> gridChangeQueue;
	};
}

#endif /* ENTITYMANAGER_HPP */