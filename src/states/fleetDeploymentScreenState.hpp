#pragma once
#include "../controllers/stateManager.hpp"
#include "../entity/ship.hpp"

class FleetDeploymentScreenState : public State {
    public:
        FleetDeploymentScreenState(StateManager& stateManager, sf::RenderWindow& window);
        ~FleetDeploymentScreenState();

        void processEvents() override;
        void update() override;
        void draw() override;

    private:
        static std::vector<sf::Sprite*> sprites;
        static std::vector<Button*> buttons;
        static std::vector<Ship*> ships;

        // TODO: add P1 & P2 indicator for Pass & Play mode

        std::vector<std::string> m_texturePaths{
            "FleetDeploymentScreen/fleetDeploymentBackground.png",
            "FleetDeploymentScreen/ship2.png",
            "FleetDeploymentScreen/ship3.png",
            "FleetDeploymentScreen/ship4.png",
            "FleetDeploymentScreen/ship5.png",
            "FleetDeploymentScreen/startButtonIdle.png",
            "FleetDeploymentScreen/startButtonActive.png",
            "FleetDeploymentScreen/homeButtonIdle.png",
            "FleetDeploymentScreen/homeButtonActive.png"
        };
        
        enum m_textureNames {
            FleetDeploymentBackgroundTexture,
            Ship2Texture,
            Ship3Texture,
            Ship4Texture,
            Ship5Texture,
            StartButtonIdleTexture,
            StartButtonActiveTexture,
            HomeButtonIdleTexture,
            HomeButtonActiveTexture
        };

        enum m_spriteNames {
            FleetDeploymentBackground,
        };

        enum m_buttonNames {
            StartButton,
            HomeButton
        };

        enum m_shipNames {
            Ship2, 
            Ship3a,
            Ship3b,
            Ship4,
            Ship5
        };
};
