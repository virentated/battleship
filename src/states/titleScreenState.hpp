#pragma once
#include "../controllers/stateManager.hpp"

class TitleScreenState : public State {
    public:
        TitleScreenState(StateManager& stateManager, sf::RenderWindow& window);
        ~TitleScreenState();

        void processEvents() override;
        void update() override;
        void draw() override;

    private:
        static std::vector<sf::Sprite*> sprites;
        static std::vector<Button*> buttons;

        std::vector<std::string> m_texturePaths{
            "TitleScreen/titleScreen.png",
            "TitleScreen/playButtonIdle.png",
            "TitleScreen/playButtonActive.png"
        };
        
        enum m_textureNames {
            TitleScreenTexture,
            PlayButtonIdleTexture,
            PlayButtonActiveTexture
        };

        enum m_spriteNames {
            TitleScreen
        };

        enum m_buttonNames {
            PlayButton
        };
};
