#include "Entity.h"

#include "ManagersMacro.h"

template<typename T>
T* Entity::getScene() const
{
	T* pScene = dynamic_cast<T*>(getScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::createEntity(float radius, const sf::Color& color)
{
	return getScene()->createEntity<T>(radius, color);
}