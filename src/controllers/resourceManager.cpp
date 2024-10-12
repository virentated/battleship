#include "resourceManager.hpp"

const std::vector<std::string> ResourceManager::TEXTURE_EXTENSIONS = {"png", "jpg", "jpeg"};

std::map<std::string, sf::Texture*> ResourceManager::m_textureMap;

sf::Texture* ResourceManager::getTexture(std::string filePath) {
  filePath = "./res/images/" + filePath;

  // Search through the map to see if there is already an entry
  if (m_textureMap.find(filePath) != m_textureMap.end()) {
      return m_textureMap[filePath];
  }

  // If the code has made it to this point, it hasn't found a matching entry
  // in the map. We use the new keyword because we want to store these variables
  // outside of the stack
  sf::Texture* texture = new sf::Texture();
  
  texture->loadFromFile(filePath);

  m_textureMap[filePath] = texture;

  return m_textureMap[filePath];
}

void ResourceManager::preLoadTextures(const std::string folderPath) {
  for (auto& file: std::filesystem::recursive_directory_iterator(folderPath)) {
    // Use a stringstream to get the path as a string here
    std::stringstream ss;
    ss << file;

    // Check the extension
    if (contains(TEXTURE_EXTENSIONS, ss.str().substr(ss.str().length() - 4, 3))) {
      sf::Texture* texture = new sf::Texture();
      texture->loadFromFile(ss.str().substr(1, ss.str().length() - 2));
      m_textureMap[ss.str().substr(1, ss.str().length() - 2)] = texture;
    }
  }

  std::cout << "Textures Loaded" << "\n";
}

void ResourceManager::clearTextures() {
  // First delete all of the pointers
  for (auto element: m_textureMap) {
    delete element.second;
  }

  // And now clear all of the entries
  m_textureMap.clear();
}

bool ResourceManager::contains(std::vector<std::string> vec, std::string str) {
  for (std::string s: vec) {
    if (s == str)
      return true;
  }
  return false;
}
