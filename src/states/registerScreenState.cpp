#include "registerScreenState.hpp"
#include "menuScreenState.hpp"

#include <iostream>

std::vector<sf::Sprite*> RegisterScreenState::sprites;
std::vector<Button*> RegisterScreenState::buttons;

RegisterScreenState::RegisterScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    // Initialize sprites if not already initialized
    if (RegisterScreenState::sprites.empty()) {
        RegisterScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::RegisterBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (RegisterScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(180*4, 80*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::RegisterButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::RegisterButtonActiveTexture]),
            m_window
        ));
    }

    std::cout << "RegisterScreenState Initialized\n";
}

RegisterScreenState::~RegisterScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);
    std::cout << "RegisterScreenState Destroyed\n";
}

void RegisterScreenState::processEvents() {
    sf::Event event;

    // TODO: add functionality to text fields
    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {
                // TODO: add conditions so register button only works when fields are filled in and username is unique
                if (event.mouseButton.button == sf::Mouse::Left && RegisterScreenState::buttons[m_buttonNames::RegisterButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                }
                return;
            }
            default:
                break;
        }
    }
}

void RegisterScreenState::update() {
    sf::Vector2f mousePosition = RegisterScreenState::getMousePosition();
    buttons[m_buttonNames::RegisterButton]->updateButtonState(mousePosition);
}

void RegisterScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : RegisterScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : RegisterScreenState::buttons) {
        button->render();
    }

    m_window.display();
}
