#include "Spritesheet.h"

#pragma region External Dependencies

#include <string>

#pragma endregion

SpriteSheet::SpriteSheet(sf::Texture* _texture, int _columns, int _rows) {
	current = 0;
	columns = _columns; rows = _rows;

	mTexture = _texture;
	mSprite.setTexture(*_texture);

	hres = _texture->getSize().x / _columns;
	vres = _texture->getSize().y / _rows;

	mSprite.setTextureRect(sf::IntRect(0, 0, hres, vres));
	mSprite.setOrigin(hres / 2.0f, vres / 2.0f);

	mIsVisible = true; 
}

void SpriteSheet::setColor(const sf::Color& color) {
	mSprite.setColor(color);
}

sf::Color SpriteSheet::getColor() const {
	return mSprite.getColor();
}

void SpriteSheet::setVisible(bool visible)
{
	mIsVisible = visible;	
}

void SpriteSheet::setTexture(sf::Texture* _texture, int _columns, int _rows) {
	mTexture = _texture;
}

void SpriteSheet::setTextureRect(sf::IntRect _rect)
{
	mSprite.setTextureRect(_rect);
}

sf::Vector2f SpriteSheet::getXY()
{
	return sf::Vector2f(current % columns, current / columns);
}

sf::Vector2f SpriteSheet::getHV()
{
	return sf::Vector2f(hres, vres);
}

void SpriteSheet::setCurrent(int _current)
{
	current = _current;
	updateViewport();
}

void SpriteSheet::updateViewport() {
	int x = current % columns;
	int y = current / columns;

	mSprite.setTextureRect(sf::IntRect(x * hres, y * vres, hres, vres));
}

void SpriteSheet::draw(sf::RenderTarget& target, sf::RenderStates states) const {

	if (!mIsVisible) return; 
	states.transform.combine(getTransform());
	target.draw(mSprite, states);
}