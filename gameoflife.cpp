#include <SFML/Graphics.hpp>

#include "debugmode.hpp"
#include "gameoflife.hpp"

#ifdef DEBUG
#include <iostream>
#endif

GameOfLife::GameOfLife(const sf::String& title, unsigned int width, unsigned int height, bool isFullScreen) {
	if (!iconImage.loadFromFile(GAME_ICON_PATH)) {
		throw std::runtime_error("Unable to load game icon image!");
	}
	// Window stuff
	auto style = (isFullScreen) ? sf::Style::Fullscreen : sf::Style::Default;
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title, style);
	window->setIcon(iconImage.getSize().x, iconImage.getSize().y, iconImage.getPixelsPtr());

	entityManager = std::make_shared<EntityManager>(BLOCK_SIZE, width - 200, height, 200, 0);
	actionControl = std::make_unique<ActionControl>(10, 10, PLAY_BUTTON_IMAGE_PATH, PAUSE_BUTTON_IMAGE_PATH, entityManager);
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

void GameOfLife::update(sf::Clock &clock) {
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

void GameOfLife::updateAllEntities(const sf::Time &deltaTime) {
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
	case sf::Event::MouseButtonPressed:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (actionControl->isButtonClicked(event.mouseButton.x, event.mouseButton.y)) {
				actionControl->whenButtonClicked();
			}
			else {
				bool state = entityManager->getEntityStateAt(event.mouseButton.x, event.mouseButton.y);
				entityManager->setEntityAt(event.mouseButton.x, event.mouseButton.y, !state);
			}
		}
	default:
		break;
	}
}

