#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <memory>
#include <queue>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "texturemanager.hpp"
#include "entity.hpp"
#include "grid.hpp"

constexpr float ENTITY_UPDATE_INTERVAL = 1;

class EntityManager {
public:
	/*
	* Sets the width and height to (width / blockSize) and (height / blockSize)
	*/
	EntityManager(unsigned int squareSize, unsigned int modeWidth, unsigned int modeHeight, 
		int xOffsetSize=0, int yOffsetSize =0);
	void initializeEntities(); // white squares with gray border
	void updateEntities(const sf::Time& deltaTime);
	void renderEntities(std::unique_ptr<sf::RenderWindow>& window);

	// Get / Set Entity Functions
	template<class T>
	void setGridEntityAt(T x, T y, bool isWhite) {
		if (static_cast<unsigned int>(x) > width || static_cast<unsigned int>(y) > height)
			return;
		auto& block = grid->at(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
		block->changeColor(isWhite);
	}

	template<class T>
	void setEntityAt(T x, T y, bool isWhite) {
		setGridEntityAt(toBlockyCoordX(x, xOffset, blockSize), toBlockyCoordY(y, yOffset, blockSize), isWhite);
	}

	template<class T>
	bool getGridEntityStateAt(T x, T y) const {
		if (static_cast<unsigned int>(x) > width || static_cast<unsigned int>(y) > height)
			return true;
		const auto& block = grid->at(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
		return block->isWhite();
	}

	template<class T>
	bool getEntityStateAt(T x, T y) const {
		return getGridEntityStateAt(toBlockyCoordX(x, xOffset, blockSize), toBlockyCoordY(y, yOffset, blockSize));
	}

	template<class T, class O, class B>
	static T toBlockyCoordX(T coordX, O xOffset, B blockSize) {
		return static_cast<T>(std::floor((coordX - xOffset) / blockSize));
	}

	template<class T, class O, class B>
	static T toBlockyCoordY(T coordY, O yOffset, B blockSize) {
		return static_cast<T>(std::floor((coordY - yOffset) / blockSize));
	}

	template<class T, class O, class B>
	static B toNormalCoordX(T gridX, O xOffset, B blockSize) {
		return static_cast<B>(gridX * blockSize) + xOffset;
	}

	template<class T, class O, class B>
	static B toNormalCoordY(T gridY, O yOffset, B blockSize) {
		return static_cast<B>(gridY * blockSize) + yOffset;
	}

	// Getters and Setters
	void setIsPlaying(bool isPlayingMotion);
	bool isPlaying() const;
private:
	void applyGameofLifeRules();
	unsigned int getNumNeighbours(int x, int y);

	// Block Stats
	unsigned int blockSize, width, height;
	int xOffset, yOffset;
	
	// Game of Life Stats
	bool isPlayingMotion;
	unsigned int generationNum;
	unsigned int populationNum;

	std::unique_ptr<Grid<std::unique_ptr<Entity>>> grid;
	std::queue<std::tuple<unsigned int, unsigned int, bool>> gridChangeQueue;
};

#endif /* ENTITYMANAGER_HPP */