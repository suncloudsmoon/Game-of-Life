#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entity.hpp"

namespace gol {
	Entity::Entity(float x, float y, float size) : sf::RectangleShape(sf::Vector2f(size, size)), isWhiteColor(true) {
		setPosition(x, y);
		// How it works: Set the main outline and change the color later
		setOutlineColor(GRAY_COLOR);
		setOutlineThickness(getSize().x * BLOCK_BORDER_THICKNESS_FACTOR);
		changeColor(true);
	}

	void Entity::changeColor(bool isWhiteCol) {
		setFillColor((isWhiteCol) ? sf::Color::White : sf::Color::Black);
		isWhiteColor = isWhiteCol;
	}

	bool Entity::isWhite() const {
		return isWhiteColor;
	}
}
