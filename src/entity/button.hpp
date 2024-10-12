#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>

class Button {
    public:
        Button(const sf::Vector2f& positionVector, const sf::Vector2f& scaleVector, 
               const sf::Texture& idleTexture, const sf::Texture& activeTexture);
        
        void render(sf::RenderWindow& window) const;

        bool getButtonState() const;
        void updateButtonState(sf::Vector2f mousePosition);

    private:
        const sf::Texture* idleTexture;
        const sf::Texture* activeTexture;
        sf::Sprite* sprite;

        bool active;
};
