#include "testState.hpp"
#include "titleScreenState.hpp"

#include <SFML/Window/Event.hpp>
#include <iostream>

TestState::TestState(StateManager& stateManager, sf::RenderWindow& window)
: State( stateManager, window ) {
    std::cout << "TestState Initialized\n";
}

TestState::~TestState() {
    std::cout << "TestState Destroyed\n";
}

void TestState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Space: {
                        std::unique_ptr<State> titleScreenState(new TitleScreenState(m_stateManager, m_window));
                        m_stateManager.changeState(std::move(titleScreenState));
                        return;
                    }
                    default:
                        break;
                }
        }
    }
}

void TestState::update() {

}

void TestState::draw() {
    m_window.clear(sf::Color::Blue);
    m_window.display();
}
