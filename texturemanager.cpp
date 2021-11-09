#include <string>

#include "texturemanager.hpp"

TextureManager::TextureManager(const std::string& blackSquarePath, const std::string& whiteSquarePath) {
	whiteSquareTexture = new sf::Texture();
	blackSquareTexture = new sf::Texture();
	
	whiteSquareTexture->loadFromFile(whiteSquarePath);
	blackSquareTexture->loadFromFile(blackSquarePath);
}

TextureManager::~TextureManager() {
	delete whiteSquareTexture;
	delete blackSquareTexture;
}

// Getters
const sf::Texture* TextureManager::getWhiteSquareTexture() const {
	return whiteSquareTexture;
}
const sf::Texture* TextureManager::getBlackSquareTexture() const {
	return blackSquareTexture;
}

