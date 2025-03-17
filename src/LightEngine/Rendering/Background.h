#pragma once

#include <SFML/system/Vector2.hpp>
#include <SFML/graphics/Rect.hpp>

#include <SFML/graphics/Drawable.hpp>
#include <SFML/graphics/Sprite.hpp>
#include <SFML/graphics/Transformable.hpp>
#include <SFML/graphics/RenderTarget.hpp>
#include <string>

class Background : public sf::Transformable, public sf::Drawable
{
protected:
    sf::Sprite* mSprite;
    sf::Texture* mTexture;
    int mWindowWidth;
    int mWindowHeight;
    float mSpeed = 0.2f;
    sf::Vector2f mUVOffset = { 0.0f, 0.0f };

public:
    Background();
    ~Background() { delete mSprite; };

    float getSpeed() const { return mSpeed; };
    void setSpeed(float speed) { mSpeed = speed; };
    void setTexture(std::string _path);
    void updateUV(float offsetX, float offsetY);

    virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
};