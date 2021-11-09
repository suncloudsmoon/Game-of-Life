#ifndef ACTIONCONTROL_HPP
#define ACTIONCONTROL_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "entitymanager.hpp"

class ActionControl {
public:
	ActionControl(float posX, float posY, const std::string &playButtonPath, const std::string &pauseButtonPath,
		const std::shared_ptr<EntityManager>& manager);
	
	void renderActionButton(std::unique_ptr<sf::RenderWindow>& window);
	void renderTextStats(std::unique_ptr<sf::RenderWindow>& window);
	bool isButtonClicked(int x, int y);
	void whenButtonClicked(); // Called when button is clicked
private:
	std::shared_ptr<EntityManager> entityManager;
	sf::Texture playButtonTexture, pauseButtonTexture;
	sf::Sprite playButton, pauseButton;

	bool isPlaying; // Initial value is false
};

#endif /* ACTIONCONTROL_HPP */