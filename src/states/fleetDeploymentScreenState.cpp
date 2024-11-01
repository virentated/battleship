#include "fleetDeploymentScreenState.hpp"
#include "menuScreenState.hpp"

#include <iostream>

std::vector<sf::Sprite*> FleetDeploymentScreenState::sprites;
std::vector<Button*> FleetDeploymentScreenState::buttons;
std::vector<Ship*> FleetDeploymentScreenState::ships;

FleetDeploymentScreenState::FleetDeploymentScreenState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {

    // Initialize sprites if not already initialized
    if (FleetDeploymentScreenState::sprites.empty()) {
        FleetDeploymentScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::FleetDeploymentBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (FleetDeploymentScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(240*4, 130*4),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::StartButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::StartButtonActiveTexture]),
            m_window
        ));

        buttons.push_back(initializeButton(
            sf::Vector2f(0, 0),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::HomeButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::HomeButtonActiveTexture]),
            m_window
        ));
    }

    // Initialize ships if not already initialized
    if (FleetDeploymentScreenState::ships.empty()) {
        ships.push_back(new Ship(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::Ship2Texture]),
            sf::Vector2f(30*4, 40*4),
            sf::Vector2f(4,4)
        ));

        ships.push_back(new Ship(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::Ship3aTexture]),
            sf::Vector2f(30*4, 70*4),
            sf::Vector2f(4,4)
        ));

        ships.push_back(new Ship(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::Ship3bTexture]),
            sf::Vector2f(30*4, 110*4),
            sf::Vector2f(4,4)
        ));

        ships.push_back(new Ship(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::Ship4Texture]),
            sf::Vector2f(60*4, 40*4),
            sf::Vector2f(4,4)
        ));

        ships.push_back(new Ship(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::Ship5Texture]),
            sf::Vector2f(60*4, 90*4),
            sf::Vector2f(4,4)
        ));
    }

    std::cout << "FleetDeploymentScreenState Initialized\n";
}

FleetDeploymentScreenState::~FleetDeploymentScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);
    std::cout << "FleetDeploymentScreenState Destroyed\n";
}

void FleetDeploymentScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {
                // If left click on home button
                if (event.mouseButton.button == sf::Mouse::Left
                 && FleetDeploymentScreenState::buttons[m_buttonNames::HomeButton]->getButtonState()) {
                    playSound("buttonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                    return;
                }

                // TODO: drag & drop functionality of ships

                // TODO: hide start button until all ships are placed

                return;
            }
            default:
                break;
        }
    }
}

void FleetDeploymentScreenState::update() {
    sf::Vector2f mousePosition = FleetDeploymentScreenState::getMousePosition();
    buttons[m_buttonNames::HomeButton]->updateButtonState(mousePosition);
    buttons[m_buttonNames::StartButton]->updateButtonState(mousePosition);
}

void FleetDeploymentScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : FleetDeploymentScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : FleetDeploymentScreenState::buttons) {
        button->render();
    }
    for (Ship* ship : FleetDeploymentScreenState::ships) {
        ship->render(m_window);
    }

    m_window.display();
}
