#pragma once

#include "Entity.h"
#include "Managers/GameManager.h"

template<typename T>
T* Scene::createEntity()
{
	static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");

	T* newEntity = new T();

	Entity* entity = newEntity;
	entity->initialize();
	
	GameManager::GetInstance()->AddEntity(newEntity);

	return newEntity;
}
