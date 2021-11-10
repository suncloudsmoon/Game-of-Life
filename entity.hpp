#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"

namespace gol {
	constexpr float BLOCK_BORDER_THICKNESS_FACTOR = 0.10f;

	const sf::Color GRAY_COLOR(184, 182, 178);

	class Entity : public sf::RectangleShape {
	public:
		/*
		* Default texture is white
		*/
		Entity(float x, float y, float size);
		void changeColor(bool isWhite);
		bool isWhite() const;
	private:
		bool isWhiteColor;
	};
}

#endif /* ENTITY_HPP */