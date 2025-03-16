#include "LvPlatformEntity.h"
#include "../RectangleCollider.h"
void LvPlatformEntity::onInitialize()
{
	setRigidBody(true);
	setKinetic(false);
}

void LvPlatformEntity::set(int x, int y)
{
	setPosition(x, y);
	setCollider(new RectangleCollider(this, sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
}
