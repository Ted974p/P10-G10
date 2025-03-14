
#pragma once

class GameManager;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>

class Scene
{
protected:
	Scene() = default;

	virtual void onInitialize() = 0;
	virtual void onEvent(const sf::Event& event) = 0;
	virtual void onUpdate() = 0;

public:
	template<typename T>
	T* createEntity();

	float getDeltaTime() const;

	int getWindowWidth() const;
	int getWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"
