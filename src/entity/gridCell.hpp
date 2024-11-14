#pragma once
#include <utility>
#include "SFML/Graphics/Rect.hpp"

class GridCell {
    public:
        GridCell();
        GridCell(const int& firstGridPosition, const int& secondGridPosition, 
                 const sf::Vector2f& globalPosition);
        ~GridCell();

        bool isInsideRect(const sf::Vector2f& position);

        sf::Vector2f getPosition();

    private:
        std::pair<int, int> m_gridPosition;

        sf::FloatRect* m_rect;
};
