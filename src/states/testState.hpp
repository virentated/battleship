#pragma once
#include "../controllers/stateManager.hpp"

class TestState : public State {
    public:
        TestState(StateManager& stateManager, sf::RenderWindow& window);
        ~TestState();

        void processEvents();
        void update();
        void draw();
};
