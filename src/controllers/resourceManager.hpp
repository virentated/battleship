#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class ResourceManager {
    private:

        const static std::vector<std::string> TEXTURE_EXTENSIONS;

    public:
        static std::map<std::string, sf::Texture*> m_textureMap;
        static sf::Texture* getTexture(const std::string filePath);

        static void preLoadTextures(const std::string folderPath);

        static void clearTextures();

        static bool contains(std::vector<std::string> vec, std::string str);
};
