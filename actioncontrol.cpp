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

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "actioncontrol.hpp"

namespace gol {
	ActionControl::ActionControl(float posX, float posY, const std::string& playButtonPath, const std::string& pauseButtonPath,
		const sf::Font &font, const std::shared_ptr<EntityManager>& manager) : entityManager(manager) {
		if (!playButtonTexture.loadFromFile(playButtonPath)) {
			throw std::runtime_error("Unable to load play button from path: " + playButtonPath + "!");
		}
		if (!pauseButtonTexture.loadFromFile(pauseButtonPath)) {
			throw std::runtime_error("Unable to load pause button from path: " + pauseButtonPath + "!");
		}
		playButton.setTexture(playButtonTexture);
		pauseButton.setTexture(pauseButtonTexture);

		playButton.setPosition(posX, posY);
		pauseButton.setPosition(posX, posY);

		// Initialize the text stuff
		generationNumText.setFont(font);
		generationNumText.setCharacterSize(50);

		populationNumText.setFont(font);
		populationNumText.setCharacterSize(50);

		isPlaying = false;
	}

	void ActionControl::renderActionButton(std::unique_ptr<sf::RenderWindow>& window) {
		if (isPlaying) {
			window->draw(pauseButton);
		}
		else {
			window->draw(playButton);
		}
	}

	void ActionControl::updateTextStats(float x, float y) {
		// Generation Text
		sf::String genStr("GEN:\n   ");
		genStr += std::to_string(entityManager->getGenerationNum());
		generationNumText.setString(genStr);
		generationNumText.setPosition(x, y);

		// Popualtion Text
		sf::String popStr("NUM:\n   ");
		popStr += std::to_string(entityManager->getPopulationCount());
		populationNumText.setString(popStr);
		populationNumText.setPosition(x, y + generationNumText.getCharacterSize() * 3);
	}

	void ActionControl::renderTextStats(std::unique_ptr<sf::RenderWindow>& window) {
		window->draw(generationNumText);
		window->draw(populationNumText);
	}

	bool ActionControl::isButtonClicked(int x, int y) {
		sf::Vector2f buttonPos;
		sf::Vector2u buttonSize;
		if (isPlaying) {
			buttonPos = pauseButton.getPosition();
			buttonSize = pauseButton.getTexture()->getSize();
		}
		else {
			buttonPos = playButton.getPosition();
			buttonSize = playButton.getTexture()->getSize();
		}
		bool xRange = static_cast<float>(x) >= buttonPos.x && x <= buttonPos.x + static_cast<float>(buttonSize.x);
		bool yRange = static_cast<float>(y) >= buttonPos.y && y <= buttonPos.y + static_cast<float>(buttonSize.y);
		return xRange && yRange;
	}

	void ActionControl::whenButtonClicked() {
		isPlaying = !isPlaying;
		entityManager->setIsPlaying(isPlaying);
	}
}
