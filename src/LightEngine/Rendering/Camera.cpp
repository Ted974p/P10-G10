#include "Camera.h"

void Camera::setLimits(float left, float right, float top, float bottom)
{
    mLeftLimit = left;
    mRightLimit = right;
    mTopLimit = top;
    mBottomLimit = bottom;
}

void Camera::setDeadzone(float left, float right, float top, float bottom)
{
    mLeftDeadzone = left;
    mRightDeadzone = right;
    mTopDeadzone = top;
    mBottomDeadzone = bottom;
}

void Camera::moveCamera(sf::Vector2f _position)
{
    sf::Vector2f center = getCenter();
    sf::Vector2f offset(0.f, 0.f);

    if (_position.x < center.x - mLeftDeadzone)
        offset.x = _position.x - (center.x - mLeftDeadzone);
    else if (_position.x > center.x + mRightDeadzone)
        offset.x = _position.x - (center.x + mRightDeadzone);

    if (_position.y < center.y - mTopDeadzone)
        offset.y = _position.y - (center.y - mTopDeadzone);
    else if (_position.y > center.y + mBottomDeadzone)
        offset.y = _position.y - (center.y + mBottomDeadzone);

    sf::Vector2f newCenter = center + offset;

    if (newCenter.x - getSize().x / 2 < mLeftLimit)
        newCenter.x = mLeftLimit + getSize().x / 2;
    if (newCenter.x + getSize().x / 2 > mRightLimit)
        newCenter.x = mRightLimit - getSize().x / 2;
    if (newCenter.y - getSize().y / 2 < mTopLimit)
        newCenter.y = mTopLimit + getSize().y / 2;
    if (newCenter.y + getSize().y / 2 > mBottomLimit)
        newCenter.y = mBottomLimit - getSize().y / 2;

    setCenter(newCenter);
}

void Camera::ajustPositionDeadzone(sf::Vector2f _position)
{
    if (_position.x < getCenter().x - mLeftDeadzone || _position.x > getCenter().x + mRightDeadzone ||
        _position.y < getCenter().y - mTopDeadzone || _position.y > getCenter().y + mBottomDeadzone)
    {
        moveCamera(_position);
    }
}

void Camera::update(float _dt)
{
    if (!mMoving) return;

    sf::Vector2f currentPosition = getCenter();
    sf::Vector2f delta = mTargetPosition - currentPosition;
    float smoothFactor = 5.0f * _dt;

    if (std::abs(delta.x) < 0.1f && std::abs(delta.y) < 0.1f)
    {
        setCenter(mTargetPosition);
        mMoving = false;
    }
    else
    {
        move(delta * smoothFactor);
    }
}