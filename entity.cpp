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
