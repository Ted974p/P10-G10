#pragma once

#include "SFML/Graphics/RenderTarget.hpp"

class Camera : public sf::View
{
private:

    float mLeftDeadzone;
    float mRightDeadzone;
    float mTopDeadzone;
    float mBottomDeadzone;

    float mLeftLimit;
    float mRightLimit;
    float mTopLimit;
    float mBottomLimit;

    sf::Vector2f mTargetPosition;
    bool mMoving;

public:

    Camera() : mMoving(false) {};
    ~Camera() = default;

    void setDeadzone(float left, float right, float top, float bottom);
    void setLimits(float left, float right, float top, float bottom);

    void ajustPositionDeadzone(sf::Vector2f _position);
    void update(float _dt);

private:

    void moveCamera(sf::Vector2f _position);
};