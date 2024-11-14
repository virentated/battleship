#include "gridCell.hpp"

GridCell::GridCell() {
    m_gridPosition.first = -1;
    m_gridPosition.second = -1;
    m_rect = nullptr;
}

GridCell::GridCell(const int& firstPosition, const int& secondPosition, const sf::Vector2f& globalPosition) {
    m_gridPosition.first = firstPosition;
    m_gridPosition.second = secondPosition;
    m_rect = new sf::FloatRect(globalPosition.x, globalPosition.y, 40, 40);
}

GridCell::~GridCell() {
    delete m_rect;
    m_rect = nullptr;
}

bool GridCell::isInsideRect(const sf::Vector2f& position) {
    return m_rect->contains(position);
}

sf::Vector2f GridCell::getPosition() {
    return m_rect->getPosition();
}
