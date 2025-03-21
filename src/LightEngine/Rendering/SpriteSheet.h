#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>

#pragma endregion

class SpriteSheet : public sf::Drawable, public sf::Transformable {
private:

	int columns, rows;
	int hres, vres;
	float mIsVisible;
	sf::Texture* mTexture;
	sf::Sprite mSprite;

public:
	int current;
	sf::Color getColor() const;
	void setColor(const sf::Color& color);
	SpriteSheet(sf::Texture* _texture = nullptr, int _columns = 0, int _rows = 0);
	void setVisible(bool visible);
	void setTexture(sf::Texture* _texture, int _columns, int _rows);
	void setTextureRect(sf::IntRect _rect);
	sf::Vector2f getXY();
	sf::Vector2f getHV();
	void setCurrent(int _current);
	void updateViewport();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};