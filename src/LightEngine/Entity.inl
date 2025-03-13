#include "Entity.h"
#include "Scene.h"

template<typename T>
T* Entity::getScene() const
{
	T* pScene = dynamic_cast<T*>(getScene());

	_ASSERT(pScene != nullptr);

	return pScene;
}


template<typename T>
T* Entity::createEntity()
{
	return getScene()->createEntity<T>();
}