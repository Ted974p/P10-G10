#include "GameManager.h"
#include "InputManager.h"

#include "../Entity.h"
#include "../Rendering/Background.h"
#include "../Rendering/Parallax.h"
#include "../Scene.h"
#include "../Utils/Debug.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

GameManager* GameManager::m_instance = nullptr;

GameManager* GameManager::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new GameManager();
	}

	return m_instance;
}

GameManager::GameManager()
{
	mParallax = new Parallax();
	mpWindow = nullptr;
	mDeltaTime = 0.0f;
	mpScene = nullptr;
	mWindowWidth = -1;
	mWindowHeight = -1;
}

GameManager::~GameManager()
{
	delete mpWindow;
	delete mpScene;

	for (Entity* entity : mEntities)
	{
		delete entity;
	}
}

void GameManager::CreateWindow(unsigned int width, unsigned int height, const char* title, int fpsLimit, sf::Color clearColor)
{
	_ASSERT(mpWindow == nullptr);

	mpWindow = new sf::RenderWindow(sf::VideoMode(width, height), title/* sf::Style::Fullscreen*/);
	mpWindow->setFramerateLimit(fpsLimit);

	mWindowWidth = width;
	mWindowHeight = height;

	mParallax->setReferencePoint(sf::Vector2f(mWindowWidth / 2, 0));

	mClearColor = clearColor;
}

void GameManager::addBackground(Background* _background)
{
	mParallax->addBackground(_background);
}

void GameManager::Run()
{
	if (mpWindow == nullptr)
	{
		std::cout << "Window not created, creating default window" << std::endl;
		CreateWindow(1280, 720, "Default window");
	}

	//#TODO : Load somewhere else
	bool fontLoaded = mFont.loadFromFile("../../../res/Hack-Regular.ttf");
	_ASSERT(fontLoaded);

	_ASSERT(mpScene != nullptr);

	sf::Clock clock;
	while (mpWindow->isOpen())
	{
		SetDeltaTime(clock.restart().asSeconds());

		HandleInput();

		Update();

		Draw();
	}
}

void GameManager::HandleInput()
{
	sf::Event event;
	while (mpWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			mpWindow->close();
		}

		inputManager->UpdateEvents(&event);

		mpScene->onEvent(event);
	}
}

void GameManager::Update()
{
	sf::Time elapsed = mFPSTimer.restart();
	mDeltaTime = elapsed.asSeconds();
	mFPS = (mDeltaTime > 0) ? 1.0f / mDeltaTime : 0.0f;

	if (mFPSUpdateTimer.getElapsedTime().asSeconds() >= 1.0f)
	{
		mFPSText = "FPS: " + std::to_string(static_cast<int>(mFPS));
		mFPSUpdateTimer.restart();
	}

	inputManager->UpdateInputs();

	mpScene->onUpdate();

	//Update
	mParallax->update();

	for (auto it = mEntities.begin(); it != mEntities.end(); )
	{
		Entity* entity = *it;
		entity->update();

		if (entity->toDestroy() == false)
		{
			++it;
		}
		else
		{
			mEntitiesToDestroy.push_back(entity);
			it = mEntities.erase(it);
		}
	}

	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1)
	{
		auto it2 = it1;
		++it2;
		for (; it2 != mEntities.end(); ++it2)
		{
			Entity* entity = *it1;
			Entity* otherEntity = *it2;

			entity->processCollision(otherEntity);
		}
	}

	for (auto it = mEntitiesToDestroy.begin(); it != mEntitiesToDestroy.end(); ++it)
	{
		delete* it;
	}
	mEntitiesToDestroy.clear();

	for (auto it = mEntitiesToAdd.begin(); it != mEntitiesToAdd.end(); ++it)
	{
		mEntities.push_back(*it);
	}
	mEntitiesToAdd.clear();
}


void GameManager::Draw()
{
	mpWindow->clear(mClearColor);

	mpWindow->draw(*mParallax);

	for (Entity* entity : mEntities)
	{
		mpWindow->draw(*entity);
		entity->showGizmos();
	}

	Debug::DrawText(10.0f, 10.0f, mFPSText, sf::Color::Black);

	Debug::Get()->Draw(mpWindow);

	mpWindow->display();
}