#include "Spritesheet.h"

#pragma region External Dependencies

#include <string>

#pragma endregion

SpriteSheet::SpriteSheet(sf::Texture* _texture, int _columns, int _rows) {
	current = 0;
	columns = _columns; rows = _rows;

	texture = _texture;
	sprite.setTexture(*texture);

	hres = texture->getSize().x / columns;
	vres = texture->getSize().y / rows;

	sprite.setTextureRect(sf::IntRect(0, 0, hres, vres));
	sprite.setOrigin(hres / 2.0f, vres / 2.0f);
}

void SpriteSheet::UpdateViewport() {
	int x = current % columns;
	int y = current / columns;

	sprite.setTextureRect(sf::IntRect(x * hres, y * vres, hres, vres));
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform.combine(getTransform());
	target.draw(sprite, states);
}