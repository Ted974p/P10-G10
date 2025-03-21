
#pragma once

class GameManager;
class Background;

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/View.hpp>

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
	Background* createBackground();

	float getDeltaTime() const;

	int getWindowWidth() const;
	int getWindowHeight() const;

	friend GameManager;
};

#include "Scene.inl"
