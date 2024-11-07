#pragma once

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(float radius, const sf::Color& color);
	void OnUpdate() override;
	void OnCollision(Entity* pCollidedWith) override;
};

