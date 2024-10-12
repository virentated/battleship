#include "button.hpp"

Button::Button(const sf::Vector2f& positionVector, const sf::Vector2f& scaleVector, 
               const sf::Texture& idleTexture, const sf::Texture& activeTexture) {
    
    this->active = false;
    this->idleTexture = &idleTexture;
    this->activeTexture = &activeTexture;

    sf::Sprite* sprite = new sf::Sprite();
    sprite->setTexture(*this->idleTexture);
    sprite->setPosition(positionVector);
    sprite->setScale(scaleVector);
    this->sprite = sprite;
}

void Button::render(sf::RenderWindow& window) const {
    sf::Cursor cursor;
    if (active) {
        cursor.loadFromSystem(sf::Cursor::Hand);
        window.setMouseCursor(cursor);
    } else {
        cursor.loadFromSystem(sf::Cursor::Arrow);
        window.setMouseCursor(cursor);
    }

    window.draw(*sprite);
}

bool Button::getButtonState() const {
    return active;
}

void Button::updateButtonState(sf::Vector2f mousePosition) {
    if (sprite->getGlobalBounds().contains(mousePosition)) {
        // If mouse is on the button
        if (!active) {
            active = true;
            sprite->setTexture(*activeTexture);
        }
    } else {
        if (active) {
            active = false;
            sprite->setTexture(*idleTexture);
        }
    }
}
