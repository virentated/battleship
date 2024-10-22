#include "ship.hpp"

Ship::Ship(const sf::Texture& texture, const sf::Vector2f& positionVector,
           const sf::Vector2f& scaleVector) {
    
    m_sprite = initializeSprite(texture, positionVector, scaleVector);
}

sf::Sprite* Ship::getSprite() {
    return m_sprite;
}

void Ship::render(sf::RenderWindow& window) const {
    window.draw(*m_sprite);
}
