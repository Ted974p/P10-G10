
#include "ResourceManager.h"

#pragma region Local Dependencies

#include "../Utils/Debug.h"
#include "../Utils/OS.h"

#pragma endregion

const std::string DEBUG_PATH = "../../../src/LightEngine/";

ResourceManager* ResourceManager::m_instance = nullptr;

ResourceManager* ResourceManager::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new ResourceManager();
	}

	return m_instance;
}

ResourceManager::ResourceManager() {
	loaded = false;

#ifdef _DEBUG
	assetPath = OS::GetAbsolutePath(DEBUG_PATH) + "Assets/";
#else
	assetPath = OS::GetExecutablePath() + "/resourcepacks/";
#endif
}

ResourceManager::~ResourceManager() {
	textures.clear();
	/*
	for (auto& pair : sounds) {
		delete pair.second.getBuffer();
		pair.second.stop();
	}
	sounds.clear();

	for (auto& pair : musics) {
		pair.second.stop();
	}
	musics.clear();
	*/
	fonts.clear();

	loaded = false;
}

void ResourceManager::LoadResources() {
	std::string root = "";
	std::string subdir = "";

#ifdef _DEBUG
	root = OS::GetAbsolutePath(DEBUG_PATH);
	subdir = "Assets/";
#else
	root = OS::GetExecutablePath();
	subdir = "/ressourcepacks/";
#endif

	std::string path = root + subdir;

	loaded = true;
}

sf::Texture* ResourceManager::GetTexture(std::string name) {

	if (textures.contains(name)) {
		return &textures[name];
	}

	std::string path = assetPath + name + ".png";
	if (!textures[name].loadFromFile(path)) {
		Debug::Assert(false, "Could not load texture: " + path);
		return nullptr;
	}

	return &textures[name];
}
std::string ResourceManager::getPath(std::string name)
{
	std::string path = assetPath + name + ".txt";
	return path;
}
/*
sf::Sound* ResourceManager::GetSound(std::string name) {
	if (!sounds.contains(name)) {
		return &sounds[name];
	}

	std::string path = assetPath + name + ".wav";
	sf::SoundBuffer* buffer = new sf::SoundBuffer;

	if (!buffer->loadFromFile(path)) {
		delete buffer;
		Debug::Assert(false, "Could not load sound: " + path);
		return nullptr;
	}

	sounds[name] = sf::Sound(*buffer);

	return &sounds[name];
}

sf::Music* ResourceManager::GetMusic(std::string name) {
	if (!musics.contains(name)) {
		return &musics[name];
	}

	std::string path = assetPath + name + ".wav";

	if (!musics[name].openFromFile(path)) {
		Debug::Assert(false, "Could not load music: " + path);
		return nullptr;
	}

	return &musics[name];
}
*/
sf::Font* ResourceManager::GetFont(std::string name) {
	if (!fonts.contains(name)) {
		return &fonts[name];
	}

	std::string path = assetPath + name + ".ttf";

	if (!fonts[name].loadFromFile(path)) {
		Debug::Assert(false, "Could not load font: " + path);
		return nullptr;
	}

	return &fonts[name];
}
