#pragma once
#include "../helpers/initializeSprite.hpp"

class Ship {
    public:
        Ship(const sf::Texture& texture, const sf::Vector2f& positionVector,
             const sf::Vector2f& scaleVector);

        sf::Sprite* getSprite();

        // TODO: drag & drop functionality

        void render(sf::RenderWindow& window) const;
    private:
        sf::Sprite* m_sprite;
};
