#include "loginScreenState.hpp"
#include "menuScreenState.hpp"
#include "registerScreenState.hpp"

#include <iostream>

std::vector<sf::Sprite*> LoginScreenState::sprites;
std::vector<Button*> LoginScreenState::buttons;

LoginScreenState::LoginScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    // Initialize sprites if not already initialized
    if (LoginScreenState::sprites.empty()) {
        LoginScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LoginBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (LoginScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(120*4, 120*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LoginButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::LoginButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(242*4, 83*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::RegisterButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::RegisterButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(242*4, 103*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::GuestButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::GuestButtonActiveTexture]),
            m_window
        ));
    }

    std::cout << "LoginScreenState Initialized\n";
}

LoginScreenState::~LoginScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);
    std::cout << "LoginScreenState Destroyed\n";
}

void LoginScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {
                // TODO: add conditions so login button only works when fields are filled in and username and password match
                if (event.mouseButton.button == sf::Mouse::Left && LoginScreenState::buttons[m_buttonNames::LoginButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                }

                // TODO: pass data as guest
                if (event.mouseButton.button == sf::Mouse::Left && LoginScreenState::buttons[m_buttonNames::GuestButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                }

                // TODO: register button logic
                if (event.mouseButton.button == sf::Mouse::Left && LoginScreenState::buttons[m_buttonNames::RegisterButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> registerScreenState(new RegisterScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(registerScreenState));
                }
                return;
            }
            default:
                break;
        }
    }
}

void LoginScreenState::update() {
    sf::Vector2f mousePosition = LoginScreenState::getMousePosition();
    buttons[m_buttonNames::LoginButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::RegisterButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::GuestButton]->updateButtonState(mousePosition);
}

void LoginScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : LoginScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : LoginScreenState::buttons) {
        button->render();
    }

    m_window.display();
}
