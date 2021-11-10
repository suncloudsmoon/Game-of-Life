#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "gameoflife.hpp"
#include "entitymanager.hpp"

#ifdef DEBUG
#include <iostream>
#endif

namespace gol {
	GameOfLife::GameOfLife(const sf::String& title, unsigned int width, unsigned int height, bool isFullScreen) {
		if (!iconImage.loadFromFile(GAME_ICON_PATH)) {
			throw std::runtime_error("Unable to load game icon image!");
		}
		// Window stuff
		int style = (isFullScreen) ? static_cast<int>(sf::Style::Fullscreen) : static_cast<int>(sf::Style::Default);
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, style);
		window->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

		// TODO: make "width - 200" a ratio not a constant
		entityManager = std::make_shared<EntityManager>(BLOCK_SIZE, width - 200, height, 200, 0);
		actionControl = std::make_unique<ActionControl>(50, 50, PLAY_BUTTON_IMAGE_PATH, PAUSE_BUTTON_IMAGE_PATH, entityManager);
	}

	void GameOfLife::start() {
		sf::Clock clock;
		setToDefaultSettings();
		initialize();
		while (window->isOpen()) {
			update(clock);
		}
	}

	void GameOfLife::setToDefaultSettings() {
		window->setVerticalSyncEnabled(true);
		window->setFramerateLimit(MAX_FRAMES_PER_SEC);
	}

	void GameOfLife::initialize() {
		entityManager->initializeEntities();
	}

	void GameOfLife::update(sf::Clock& clock) {
		// Update deltaTime
		sf::Time deltaTime = clock.restart();

		// Updating key events
		sf::Event event;
		while (window->pollEvent(event)) {
			handleAllUserInteractions(event);
		}
		// Updating calculations
		updateAllEntities(deltaTime);

		// Updating Graphics
		window->clear(CLEAR_WINDOW_COLOR);
		drawAllEntities();
		window->display();
	}

	void GameOfLife::updateAllEntities(const sf::Time& deltaTime) {
		entityManager->updateEntities(deltaTime);
	}

	void GameOfLife::drawAllEntities() {
		entityManager->renderEntities(window);
		actionControl->renderActionButton(window);
	}

	void GameOfLife::handleAllUserInteractions(const sf::Event& event) {
		switch (event.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::MouseButtonPressed: {
			int x = event.mouseButton.x;
			int y = event.mouseButton.y;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (actionControl->isButtonClicked(x, y)) {
					actionControl->whenButtonClicked();
				}
				else if (entityManager->isWithinGrid(x, y)) {
					bool state = entityManager->getEntityStateAt(x, y);
					entityManager->setEntityStateAt(x, y, !state);
				}
			}
		}
		default:
			break;
		}
	}
}
