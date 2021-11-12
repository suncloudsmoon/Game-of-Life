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

#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP

#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"
#include "actioncontrol.hpp"

namespace gol {
	constexpr unsigned int MAX_FRAMES_PER_SEC = 60;
	constexpr unsigned int BLOCK_SIZE = 50;

	const sf::Color CLEAR_WINDOW_COLOR = sf::Color::Black;
	const std::string GAME_ICON_PATH = "res/icon.png";
	const std::string PLAY_BUTTON_IMAGE_PATH = "res/play.png";
	const std::string PAUSE_BUTTON_IMAGE_PATH = "res/pause.png";

	class GameOfLife {
	public:
		GameOfLife(const sf::String& title, unsigned int width, unsigned int height, bool isFullScreen);
		void start();
	private:
		void setToDefaultSettings();
		void initialize();

		void update(sf::Clock& clock);
		void updateAllEntities(const sf::Time& deltaTime);
		void drawAllEntities();

		void handleAllUserInteractions(const sf::Event& event);

		sf::Image iconImage;
		sf::Font font;
		std::unique_ptr<sf::RenderWindow> window;
		std::shared_ptr<EntityManager> entityManager;
		std::unique_ptr<ActionControl> actionControl;

	};
}

#endif /* GAMEOFLIFE_HPP */