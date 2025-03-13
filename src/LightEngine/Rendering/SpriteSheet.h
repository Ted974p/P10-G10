#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>

#pragma endregion

class SpriteSheet : public sf::Drawable, public sf::Transformable {
private:
	int columns, rows;
	int hres, vres;

	sf::Texture* texture;
	sf::Sprite sprite;

public:
	int current;
	SpriteSheet(sf::Texture* _texture, int _columns, int _rows);
	
	void UpdateViewport();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};