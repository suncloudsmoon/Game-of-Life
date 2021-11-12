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

#ifndef ACTIONCONTROL_HPP
#define ACTIONCONTROL_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"

namespace gol {
	class ActionControl {
	public:
		ActionControl(float posX, float posY, const std::string& playButtonPath, const std::string& pauseButtonPath,
			const sf::Font &font, const std::shared_ptr<EntityManager>& manager);

		void renderActionButton(std::unique_ptr<sf::RenderWindow>& window);
		void updateTextStats(float x, float y);
		void renderTextStats(std::unique_ptr<sf::RenderWindow>& window);
		bool isButtonClicked(int x, int y);
		void whenButtonClicked(); // Called when button is clicked
	private:
		std::shared_ptr<EntityManager> entityManager;
		sf::Texture playButtonTexture, pauseButtonTexture;
		sf::Sprite playButton, pauseButton;

		sf::Text generationNumText, populationNumText;

		bool isPlaying; // Initial value is false
	};
}

#endif /* ACTIONCONTROL_HPP */