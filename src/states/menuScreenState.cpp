#include "menuScreenState.hpp"

#include <iostream>

std::vector<sf::Sprite*> MenuScreenState::sprites;
std::vector<Button*> MenuScreenState::buttons;

MenuScreenState::MenuScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    m_usernameText = *initializeText("TestUser", sf::Vector2f(25*4, 4*4), 20 * 4, sf::Color::White);

    // Initialize sprites if not already initialized
    if (MenuScreenState::sprites.empty()) {
        MenuScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::MenuBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (MenuScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(0, 40*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PlayVsBotButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PlayVsBotButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(110*4, 40*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PassAndPlayButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PassAndPlayButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(220*4, 40*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LeaderboardButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LeaderboardButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(0, 0),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::UserSettingsButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::UserSettingsButtonActiveTexture]),
            m_window
        ));
    }

    std::cout << "MenuScreenState Initialized\n";
}

MenuScreenState::~MenuScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);
    std::cout << "MenuScreenState Destroyed\n";
}

void MenuScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;

            // TODO: add functionality to buttons

            default:
                break;
        }
    }
}

void MenuScreenState::update() {
    sf::Vector2f mousePosition = MenuScreenState::getMousePosition();
    buttons[m_buttonNames::PlayVsBotButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::PassAndPlayButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::LeaderboardButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::UserSettingsButton]->updateButtonState(mousePosition);
}

void MenuScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : MenuScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : MenuScreenState::buttons) {
        button->render();
    }

    m_window.draw(m_usernameText);

    m_window.display();
}
