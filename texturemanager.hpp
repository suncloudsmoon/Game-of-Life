#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <string>

#include <SFML/Graphics.hpp>

class TextureManager {
public:
	/*
	* Black and White
	*/
	TextureManager(const std::string& blackSquarePath, const std::string& whiteSquarePath);
	~TextureManager();

	const sf::Texture* getWhiteSquareTexture() const;
	const sf::Texture* getBlackSquareTexture() const;
private:
	sf::Texture* whiteSquareTexture;
	sf::Texture* blackSquareTexture;
};

#endif /* TEXTUREMANAGER_HPP */