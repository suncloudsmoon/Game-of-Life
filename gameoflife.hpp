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
		std::unique_ptr<sf::RenderWindow> window;
		std::shared_ptr<EntityManager> entityManager;
		std::unique_ptr<ActionControl> actionControl;
	};
}

#endif /* GAMEOFLIFE_HPP */