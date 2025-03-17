#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>

#pragma endregion

class SpriteSheet : public sf::Drawable, public sf::Transformable {
private:

	int columns, rows;
	int hres, vres;

	sf::Texture* mTexture;
	sf::Sprite mSprite;

public:
	int current;
	SpriteSheet(sf::Texture* _texture = nullptr, int _columns = 0, int _rows = 0);
	
	void setTexture(sf::Texture* _texture, int _columns, int _rows);
	void setTextureRect(sf::IntRect _rect);
	void updateViewport();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};