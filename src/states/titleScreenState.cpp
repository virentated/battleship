#include "titleScreenState.hpp"
#include "testState.hpp"

#include <iostream>

std::vector<sf::Sprite*> TitleScreenState::sprites;
std::vector<Button*> TitleScreenState::buttons;

TitleScreenState::TitleScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    // Initialize sprites if not already initialized
    if (TitleScreenState::sprites.empty()) {
        TitleScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::TitleScreenTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (TitleScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(210*4, 110*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PlayButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::PlayButtonActiveTexture])
        ));
    }

    std::cout << "TitleScreenState Initialized\n";
}

TitleScreenState::~TitleScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);
    std::cout << "TitleScreenState Destroyed\n";
}

void TitleScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {
                if (event.mouseButton.button == sf::Mouse::Left && TitleScreenState::buttons[m_buttonNames::PlayButton]->getButtonState()) {
                    std::unique_ptr<State> testState(new TestState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(testState));
                }
                return;
            }
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space: {
                        std::unique_ptr<State> titleScreenState(new TestState(m_stateManager, m_window));
                        m_stateManager.changeState(std::move(titleScreenState));
                        return;
                    }
                    default:
                        break;
                }
            default:
                break;
        }
    }
}

void TitleScreenState::update() {
    sf::Vector2f mousePosition = TitleScreenState::getMousePosition();
    buttons[m_buttonNames::PlayButton]->updateButtonState(mousePosition);
}

void TitleScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : TitleScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : TitleScreenState::buttons) {
        button->render(m_window);
    }

    m_window.display();
}
