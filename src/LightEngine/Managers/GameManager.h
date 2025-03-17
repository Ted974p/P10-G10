#pragma once

#include <list>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

class Entity;
class Background;
class Parallax;
class Scene;
class Debug;

namespace sf
{
	class RenderWindow;
	class Event;
}

class GameManager
{
	static GameManager* m_instance;

	std::list<Entity*> mEntities;
	std::list<Entity*> mEntitiesToDestroy;
	std::list<Entity*> mEntitiesToAdd;

	Parallax* mParallax;

	sf::RenderWindow* mpWindow;
	sf::Font mFont;

	Scene* mpScene;

	float mDeltaTime;

	int mWindowWidth;
	int mWindowHeight;

	sf::Clock mFPSTimer;
	sf::Clock mFPSUpdateTimer;
	float mFPS = 0.0f;
	std::string mFPSText = "FPS: 0";

	sf::Color mClearColor;

private:

	void Run();

	void HandleInput();
	void Update();
	void Draw();

	void SetDeltaTime(float deltaTime) { mDeltaTime = deltaTime; }


	GameManager();

public:

	static GameManager* GetInstance();

	~GameManager();

	void CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit = 60, sf::Color clearColor = sf::Color::Black);

	template<typename T>
	void LaunchScene();

	float GetDeltaTime() const { return mDeltaTime; }
	Parallax* getParallax() const { return mParallax; }

	Scene* GetScene() const { return mpScene; }
	sf::Font& GetFont() { return mFont; };
	sf::RenderWindow* GetWindow() const { return mpWindow; }
	float GetWindowHeight() const { return mWindowHeight; }
	float GetWindowWidth() const { return mWindowWidth; }

	void addBackground(Background* _background);
	void AddEntity(Entity* entity) { mEntitiesToAdd.push_back(entity); }
	std::list<Entity*> getEntities() const { return mEntities; };

	friend Debug;
	friend Scene;
};

#include "GameManager.inl"

#define gameManager GameManager::GetInstance()