#pragma once

#pragma region External Dependencies

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <string>
#include <map>

#pragma endregion

class ResourceManager {
private:

	static ResourceManager* m_instance;

	std::string assetPath;

	bool loaded;

	std::map<std::string, sf::Texture> textures;
	//std::map<std::string, sf::Sound> sounds;
	//std::map<std::string, sf::Music> musics;
	std::map<std::string, sf::Font> fonts;

	ResourceManager();


public:

	static ResourceManager* GetInstance();
	~ResourceManager();

	void LoadResources();

	sf::Texture* GetTexture(std::string name);

	//sf::Sound* GetSound(std::string name);

	//sf::Music* GetMusic(std::string name);

	sf::Font* GetFont(std::string name);
	std::string getTxt(std::string name);
};

#define resourceManager ResourceManager::GetInstance()
