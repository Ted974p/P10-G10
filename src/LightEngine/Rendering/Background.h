#pragma once

#include <SFML/system/Vector2.hpp>
#include <SFML/graphics/Rect.hpp>

#include <SFML/graphics/Drawable.hpp>
#include <SFML/graphics/Transformable.hpp>
#include <SFML/graphics/RenderTarget.hpp>
#include <string>

class SpriteSheet;

class Background : public sf::Transformable, public sf::Drawable
{
protected:

    SpriteSheet* mSpriteSheet;
    int mWindowWidth;
    int mWindowHeight;
    float mSpeed = 0.2f;
    int mTag = -1;

public:

    Background();
    ~Background() { delete mSpriteSheet; };

    void setScale(int _windowWidth, int _windowHeight);
    void setSpeed(float speed) { mSpeed = speed; };
    void setTexture(std::string _path, int _columns, int _rows);

    virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
};