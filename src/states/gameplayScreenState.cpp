#include "gameplayScreenState.hpp"
#include "menuScreenState.hpp"
#include "../helpers/copy2dArray.hpp"
#include "../helpers/generateRandomBoard.hpp"
#include "../botLogic/bot.h"
#include "../helpers/convertArrayToVector.hpp"
#include <vector>
#include <iostream>

std::vector<sf::Sprite*> GameplayScreenState::sprites;
std::vector<Button*> GameplayScreenState::buttons;

GameplayScreenState::GameplayScreenState(StateManager& stateManager, sf::RenderWindow& window,
 bool isMultiplayer, int player1Grid[12][12], int player2Grid[12][12], int difficulty)
 : State( stateManager, window ), m_isMultiplayer(isMultiplayer) {

    // Initialize ship locations
    // Player ship locations
    copy2dArray(player1Grid, m_playerShipLocations);

    // Enemy ship locations
    std::vector<std::vector<int>> enemyShipLocationsVector = generateRandomBoard();
    for (int i = 0; i <12; ++i) {
      for (int j = 0; j <12; ++j) {
        m_enemyShipLocations[i][j] = enemyShipLocationsVector[i][j];
        std::cout << m_enemyShipLocations[i][j] << " ";
      }
      std::cout << std::endl;
   }

    // Get bot moves
    Bot* bot = new Bot();
    botBoardStates = bot->playGame(
        convertArrayToVector(m_playerShipLocations),
        difficulty
    );
    delete bot;
    bot = nullptr;

    // Initialize sprites if not already initialized
    if (GameplayScreenState::sprites.empty()) {
        GameplayScreenState::sprites.push_back(initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::GameplayScreenBackgroundTexture]),
            sf::Vector2f(0,0),
            sf::Vector2f(4,4)
        ));
    }

    // Initialize buttons if not already initialized
    if (GameplayScreenState::buttons.empty()) {
        buttons.push_back(initializeButton(
            sf::Vector2f(0, 0),
            sf::Vector2f(4, 4),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::GiveUpButtonIdleTexture]),
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::GiveUpButtonActiveTexture]),
            m_window
        ));
    }

    // Initialize Mini-Grid
    int startWidth = 20 * 4;
    int startHeight = 60 * 4;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            m_miniGrid[i][j] = new MiniGridCell(
                i, 
                j, 
                sf::Vector2f(startWidth + (j * 20), startHeight + (i * 20))
            );

            switch (m_playerShipLocations[i][j]) {
                case 1:
                    m_miniGrid[i][j]->setBottomTexture(
                        m_miniGridCellTextures::MiniShipBlueTexture
                    );
                    break;
                case 2:
                    m_miniGrid[i][j]->setBottomTexture(
                        m_miniGridCellTextures::MiniShipGreenTexture
                    );
                    break;
                case 3:
                    m_miniGrid[i][j]->setBottomTexture(
                        m_miniGridCellTextures::MiniShipPinkTexture
                    );
                    break;
                case 4:
                    m_miniGrid[i][j]->setBottomTexture(
                        m_miniGridCellTextures::MiniShipOrangeTexture
                    );
                    break;
                case 5:
                    m_miniGrid[i][j]->setBottomTexture(
                        m_miniGridCellTextures::MiniShipYellowTexture
                    );
                    break;
                default:
                    break;
            }

        }
    }

    // Initialize grid boundary
    m_gridBoundary = new sf::FloatRect(
        sf::Vector2f(100*4, 30*4),
        sf::Vector2f(120*4, 120*4)
    );

    // Initialize Grid
    startWidth = 100 * 4;
    startHeight = 30 * 4;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            m_grid[i][j] = new GridCell(
                i, 
                j, 
                sf::Vector2f(startWidth + (j * 40), startHeight + (i * 40)),
                true
            );
        }
    }

    // Initialize Ship X's
    for (int i = 0; i < 2; i++) {
        m_blueShipXs[i] = initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::ShipCubeHitTexture]),
            sf::Vector2f(250 * 4, (40 + i * 10) * 4),
            sf::Vector2f(4,4)
        );
    }
    for (int i = 0; i < 3; i++) {
        m_greenShipXs[i] = initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::ShipCubeHitTexture]),
            sf::Vector2f(250 * 4, (70 + i * 10) * 4),
            sf::Vector2f(4,4)
        );
    }
    for (int i = 0; i < 3; i++) {
        m_pinkShipXs[i] = initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::ShipCubeHitTexture]),
            sf::Vector2f(250 * 4, (110 + i * 10) * 4),
            sf::Vector2f(4,4)
        );
    }
    for (int i = 0; i < 4; i++) {
        m_orangeShipXs[i] = initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::ShipCubeHitTexture]),
            sf::Vector2f(280 * 4, (40 + i * 10) * 4),
            sf::Vector2f(4,4)
        );
    }
    for (int i = 0; i < 5; i++) {
        m_yellowShipXs[i] = initializeSprite(
            *ResourceManager::getTexture(m_texturePaths[m_textureNames::ShipCubeHitTexture]),
            sf::Vector2f(280 * 4, (90 + i * 10) * 4),
            sf::Vector2f(4,4)
        );
    }

    std::cout << "GameplayScreenState Initialized\n";
}

GameplayScreenState::~GameplayScreenState() {
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Arrow);
    m_window.setMouseCursor(cursor);

    // Delete MiniGridCells
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            delete m_miniGrid[i][j];
            m_miniGrid[i][j] = nullptr;
        }
    }

    // Delete GridCells
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            delete m_grid[i][j];
            m_grid[i][j] = nullptr;
        }
    }

    // Delete grid boundary
    delete m_gridBoundary;
    m_gridBoundary = nullptr;

    // Delete ship X's
    for (sf::Sprite* sprite : m_blueShipXs) {
        delete sprite;
        sprite = nullptr;
    }
    for (sf::Sprite* sprite : m_greenShipXs) {
        delete sprite;
        sprite = nullptr;
    }
    for (sf::Sprite* sprite : m_pinkShipXs) {
        delete sprite;
        sprite = nullptr;
    }
    for (sf::Sprite* sprite : m_orangeShipXs) {
        delete sprite;
        sprite = nullptr;
    }
    for (sf::Sprite* sprite : m_yellowShipXs) {
        delete sprite;
        sprite = nullptr;
    }

    std::cout << "GameplayScreenState Destroyed\n";
}

bool GameplayScreenState::isShipSunk(int shipNumberIndicator, int row, int col) {
    // Check to the left
    int tempIndex = col;
    while (tempIndex > 0) {
        tempIndex--;
        if (m_enemyShipLocations[row][tempIndex] == shipNumberIndicator) 
            return false;
    }

    // Check to the right
    tempIndex = col;
    while (tempIndex < 11) {
        tempIndex++;
        if (m_enemyShipLocations[row][tempIndex] == shipNumberIndicator) 
            return false;
    }

    // Check up
    tempIndex = row;
    while (tempIndex > 0) {
        tempIndex--;
        if (m_enemyShipLocations[tempIndex][col] == shipNumberIndicator) 
            return false;
    }

    // Check down
    tempIndex = row;
    while (tempIndex < 11) {
        tempIndex++;
        if (m_enemyShipLocations[tempIndex][col] == shipNumberIndicator) 
            return false;
    }

    switch (shipNumberIndicator) {
        case 1:
            m_blueSank = true;
            break;
        case 2:
            m_greenSank = true;
            break;
        case 3:
            m_pinkSank = true;
            break;
        case 4:
            m_orangeSank = true;
            break;
        case 5:
            m_yellowSank = true;
            break;
        default:
            break;
    }
    return true;
}

void GameplayScreenState::processEvents() {
    sf::Event event;

    while (m_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                m_stateManager.quit();
                break;
            case sf::Event::MouseButtonReleased: {

                // If left click on grid cell
                sf::Vector2f mousePosition = getMousePosition();
                if (event.mouseButton.button == sf::Mouse::Left && isMouseInGrid) {
                    for (int i = 0; i < 12; i++) {
                        for (int j = 0; j < 12; j++) {
                            if (m_grid[i][j]->isInsideRect(mousePosition)
                             && m_gridHitMap[i][j] == 0) {

                                if (m_enemyShipLocations[i][j] == 0) {
                                    // If miss
                                    m_grid[i][j]->setSpriteTexture(
                                        m_gridCellTextures::MissTexture
                                    );

                                    playSound("shipMiss.wav");
                                } else {
                                    // If hit
                                    m_grid[i][j]->setSpriteTexture(
                                        m_gridCellTextures::HitTexture
                                    );

                                    // Check if ship sank
                                    int currentShipIndicator = m_enemyShipLocations[i][j];
                                    m_enemyShipLocations[i][j] = 0;  // Set enemy ship location back to 0

                                    if (isShipSunk(currentShipIndicator, i, j)) {
                                        // Ship sank
                                        playSound("shipSink.wav");
                                    } else {
                                        // Ship still alive
                                        playSound("shipHit.wav");
                                    }

                                }

                                m_gridHitMap[i][j] = 1;
                            }
                        }
                    }
                    return;
                }
                
                // If left click on Give Up button
                if (event.mouseButton.button == sf::Mouse::Left
                 && GameplayScreenState::buttons[m_buttonNames::GiveUpButton]->getButtonState()) {
                    playSound("logoutButtonSelect.wav");
                    std::unique_ptr<State> menuScreenState(new MenuScreenState(m_stateManager, m_window));
                    m_stateManager.changeState(std::move(menuScreenState));
                    return;
                }
                return;
            }
            default:
                break;
        }
    }
}

void GameplayScreenState::update() {
    sf::Vector2f mousePosition = GameplayScreenState::getMousePosition();
    buttons[m_buttonNames::GiveUpButton]->updateButtonState(mousePosition);

    isMouseInGrid = m_gridBoundary->contains(mousePosition) ? true : false;
    
}

void GameplayScreenState::draw() {
    m_window.clear();

    for (sf::Sprite* sprite : GameplayScreenState::sprites) {
        m_window.draw(*sprite);
    }
    for (Button* button : GameplayScreenState::buttons) {
        button->render();
    }

    // Render MiniGridCells
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
             m_miniGrid[i][j]->render(m_window);
        }
    }

    // Render GridCells
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
             m_grid[i][j]->render(m_window);
        }
    }

    // Render Ship X's
    if (m_blueSank) {
        for (sf::Sprite* sprite : m_blueShipXs) {
            m_window.draw(*sprite);
        }
    }
    if (m_greenSank) {
        for (sf::Sprite* sprite : m_greenShipXs) {
            m_window.draw(*sprite);
        }
    }
    if (m_pinkSank) {
        for (sf::Sprite* sprite : m_pinkShipXs) {
            m_window.draw(*sprite);
        }
    }
    if (m_orangeSank) {
        for (sf::Sprite* sprite : m_orangeShipXs) {
            m_window.draw(*sprite);
        }
    }
    if (m_yellowSank) {
        for (sf::Sprite* sprite : m_yellowShipXs) {
            m_window.draw(*sprite);
        }
    }

    m_window.display();
}

