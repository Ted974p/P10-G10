#include "Background.h"

#include "../Managers/ResourceManager.h"
#include "../Managers/GameManager.h"

Background::Background()
{
    mSprite = new sf::Sprite();
    mTexture = nullptr;

    mWindowHeight = gameManager->GetWindowHeight();
    mWindowWidth = gameManager->GetWindowWidth();
}

void Background::setTexture(std::string _path)
{
    mTexture = resourceManager->GetTexture(_path);
    if (mTexture)
    {
        mTexture->setRepeated(true);
        mSprite->setTexture(*mTexture);

        // Adapter la texture pour qu'elle couvre tout l'écran
        mSprite->setTextureRect(sf::IntRect(0, 0, mWindowWidth, mWindowHeight));
    }
}

void Background::updateUV(float offsetX, float offsetY)
{
    mUVOffset.x = offsetX;
    mUVOffset.y = offsetY;
    mSprite->setTextureRect(sf::IntRect(static_cast<int>(mUVOffset.x) % mWindowWidth, static_cast<int>(mUVOffset.y) % mWindowHeight, mWindowWidth, mWindowHeight));
}

void Background::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    if (mSprite) {
        _states.transform.combine(getTransform());
        _target.draw(*mSprite, _states);
    }
}
