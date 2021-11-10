#include <memory>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "actioncontrol.hpp"

namespace gol {
	ActionControl::ActionControl(float posX, float posY, const std::string& playButtonPath, const std::string& pauseButtonPath,
		const std::shared_ptr<EntityManager>& manager) : entityManager(manager) {
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
