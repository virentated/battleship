#pragma once
#include "../controllers/stateManager.hpp"

class RegisterScreenState : public State {
    public:
        RegisterScreenState(StateManager& stateManager, sf::RenderWindow& window);
        ~RegisterScreenState();

        void processEvents() override;
        void update() override;
        void draw() override;

    private:
        static std::vector<sf::Sprite*> sprites;
        static std::vector<Button*> buttons;

        std::vector<std::string> m_texturePaths{
            "RegisterScreen/registerBackground.png",
            "RegisterScreen/registerButtonIdle.png",
            "RegisterScreen/registerButtonActive.png",
        };
        
        enum m_textureNames {
            RegisterBackgroundTexture,
            RegisterButtonIdleTexture,
            RegisterButtonActiveTexture,
        };

        enum m_spriteNames {
            RegisterBackground
        };

        enum m_buttonNames {
            RegisterButton
        };
};