#include "Background.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/GameManager.h"

#include "SpriteSheet.h"

Background::Background()
{
    mSpriteSheet = new SpriteSheet();

    mWindowHeight = gameManager->GetWindowHeight();
    mWindowWidth = gameManager->GetWindowWidth();
}

void Background::setTexture(std::string _path, int _columns, int _rows)
{
    sf::Texture* texture = resourceManager->GetTexture(_path);
    if (texture)
    {
        texture->setRepeated(true);
        mSpriteSheet->setTexture(texture, _columns, _rows);

        mSpriteSheet->setTextureRect(sf::IntRect(0, 0, mWindowWidth, mWindowHeight));
    }

    mSpriteSheet = new SpriteSheet(resourceManager->GetTexture(_path), _columns, _rows);
}

void Background::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    _states.transform.combine(getTransform());

    if (mSpriteSheet) {
        _target.draw(*mSpriteSheet, _states);
    }
};
