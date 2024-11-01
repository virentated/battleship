//
// Created by Jan on 2024-09-17.
//

#include "bot.h"

void Bot::initializeMap(int boardSize) {

    probBoard.resize(boardSize, vector<int>(boardSize, 0));
    for (int shipSize : ships) {
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                // Horizontal placement
                if (j + shipSize <= boardSize) {
                    vector<pair<int, int>> shipCoords;
                    for (int k = 0; k < shipSize; k++) {
                        shipCoords.emplace_back(i, j + k);
                    }
                    potentialShips.push_back(shipCoords);
                }

                // Vertical placement
                if (i + shipSize <= boardSize) {
                    vector<pair<int, int>> shipCoords;
                    for (int k = 0; k < shipSize; k++) {
                        shipCoords.emplace_back(i + k, j);
                    }
                    potentialShips.push_back(shipCoords);
                }
            }
        }
    }
}
void Bot::fillProbBoard() {
    for (auto& row : probBoard) {
        fill(row.begin(), row.end(), 0);
    }

    for (const auto& ship : potentialShips) {
        for (const auto& coord : ship) {
            probBoard[coord.first][coord.second] += 1;
        }
    }
}
void Bot::fillProbBoard(const vector<vector<pair<int,int>>>& potentialShips) {
    for (auto& row : probBoard) {
        fill(row.begin(), row.end(), 0);
    }

    for (const auto& ship : potentialShips) {
        for (const auto& coord : ship) {
            probBoard[coord.first][coord.second] += 1;
        }
    }
}

pair<int, int> Bot::findHighestProb(const std::vector<std::pair<int, int>>& usedValues = {}) const {
    int maxValue = 0;
    pair<int, int> maxIndex = {-1, -1};

    for (int i = 0; i < probBoard.size(); i++) {
        for (int j = 0; j < probBoard[i].size(); j++) {
            pair<int, int> currentIndex = {i, j};
            if (probBoard[i][j] > maxValue &&
                std::find(usedValues.begin(), usedValues.end(), currentIndex) == usedValues.end()) {
                maxValue = probBoard[i][j];
                maxIndex = currentIndex;
                }
        }
    }
    return maxIndex;
}

vector<vector<pair<int, int>>> Bot::findShips(
    const vector<pair<int, int>>& coordinates,
    const pair<int, int>& badCoordinate = {-1,-1}
) {
    vector<vector<pair<int, int>>> matchingShips;

    for (const auto& ship : potentialShips) {
        bool allFound = true;

        for (const auto& coord : coordinates) {
            if (std::find(ship.begin(), ship.end(), coord) == ship.end()) {
                allFound = false;
                break;
            }
        }
        if (allFound && std::find(ship.begin(), ship.end(), badCoordinate) == ship.end()) {
            matchingShips.push_back(ship);
        }
    }
    return matchingShips;
}



void Bot::removeShips(pair<int,int> nextSquare) {
    potentialShips.erase(remove_if(potentialShips.begin(), potentialShips.end(),
        [&nextSquare](const vector<pair<int, int>>& ship) {
        return find(ship.begin(), ship.end(), nextSquare) != ship.end();
    }), potentialShips.end());
}

vector<vector<pair<int, int>>>  Bot::removeShips(vector<vector<pair<int,int>>> hitShips, pair<int,int> nextSquare) {
    hitShips.erase(remove_if(hitShips.begin(), hitShips.end(),
        [&nextSquare](const vector<pair<int, int>>& ship) {
        return find(ship.begin(), ship.end(), nextSquare) != ship.end();
    }), hitShips.end());
    return hitShips;
}


void Bot::printProbBoard(const int boardSize) const {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            std::cout << std::setw(3) << probBoard[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

void Bot::printShipBoard(const vector<vector<int>> &shipLocations) {
    for (int i = 0; i < shipLocations.size(); ++i) {
        for (int j = 0; j < shipLocations.size(); ++j) {
            std::cout << std::setw(3) << shipLocations[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "\n" << std::endl;
}

bool Bot::shipOnBoard(int shipVal, const vector<vector<int>>& shipLocations) {
    for (const auto& row : shipLocations) {
        for (int element : row) {
            if (element == shipVal) {
                return true; // Found the target
            }
        }
    }
    return false; // Target not found
}

void Bot::hitOnBoard(const vector<vector<int>>& shipLocations) {
    for (int i = 0; i < shipLocations.size(); ++i) {
        for (int j = 0; j < shipLocations.size(); ++j) {
            if (shipLocations[i][j] > 100) {
                pair<int, int> hit = {i, j};
                hitShips.emplace_back(hit); // Found the target
            }
        }
    }
}

bool Bot::shipsLeft(const vector<vector<int>>& shipLocations) {
    for (const auto& row : shipLocations) {
        for (const int element : row) {
            if (element > 0 && element < 50) {
                return true; // Found the target
            }
        }
    }
    return false; // Target not found
}

void Bot::hitLogic(const pair<int, int> &nextSquare,vector<vector<int>>& shipLocations, int shipVal) {
    shipLocations[nextSquare.first][nextSquare.second] += 100;
    pair<int, int> nextShot = nextSquare;
    hitSquares.push_back(nextSquare);
    vector<vector<pair<int,int>>> possShips;

    while(shipOnBoard(shipVal, shipLocations)) {
        boardStates.emplace_back(shipLocations);
        if (hitSquares.size() > 5) {
            possShips = findShips({hitSquares.front()});
            fillProbBoard(possShips);

            for (auto it = hitSquares.begin() + 1; it != hitSquares.end(); ++it) {
                probBoard[it->first][it->second] = 0;
            }

        } else if (shipOnBoard(shipVal, shipLocations) && nextShot.first == -1 && nextShot.second == -1) {
            possShips = findShips({hitSquares.front()});
            fillProbBoard(possShips);

            for (auto it = hitSquares.begin() + 1; it != hitSquares.end(); ++it) {
                probBoard[it->first][it->second] = 0;
            }
        }
        else {
            possShips = findShips(hitSquares);
            fillProbBoard(possShips);
        }

        nextShot = findHighestProb(hitSquares);
        if (nextShot.first == -1 && nextShot.second == -1) {
            possShips = findShips({hitSquares.front()});
            fillProbBoard(possShips);

            for (auto it = hitSquares.begin() + 1; it != hitSquares.end(); ++it) {
                probBoard[it->first][it->second] = 0;
            }
            nextShot = findHighestProb(hitSquares);
        }
        if (shipLocations[nextShot.first][nextShot.second] == 0) {
            removeShips(nextShot);
            shipLocations[nextShot.first][nextShot.second] -= 100;
        } else {
            hitSquares.emplace_back(nextShot);
            shipLocations[nextShot.first][nextShot.second] += 100;
        }
    }
    int sunkShip = shipLocations[hitSquares.back().first][hitSquares.back().second];

    for (const auto& ship : hitSquares) {
        if (shipLocations[ship.first][ship.second] == sunkShip) {
            shipLocations[ship.first][ship.second] -= 200;
            removeShips(ship);
        }
    }
    hitOnBoard(shipLocations);
    hitSquares.clear();

    if (!hitShips.empty()) {
        const pair<int,int> hitShot = hitShips.front();

        for (const auto& ship : hitShips) {
            shipVal = shipLocations[hitShot.first][hitShot.second];
            if (shipLocations[ship.first][ship.second] == shipVal) {
                hitSquares.emplace_back(ship);
            }
        }

        hitShips.erase(
    std::remove_if(hitShips.begin(), hitShips.end(),
        [&](const pair<int, int>& ship) {
            return shipLocations[ship.first][ship.second] ==
                   shipLocations[hitShot.first][hitShot.second];
        }),
    hitShips.end()
);
        shipLocations[hitShot.first][hitShot.second] -= 100;
        hitLogic(hitShot, shipLocations, shipLocations[hitShot.first][hitShot.second]);
    }
}

vector<vector<vector<int>>> Bot::playGame(vector<vector<int>> shipLocations) {

    const int boardSize = shipLocations.size();
    initializeMap(boardSize);
    fillProbBoard(potentialShips);
    while (!potentialShips.empty() and shipsLeft(shipLocations)) {

        pair<int, int> nextSquare = findHighestProb();
        if (shipLocations[nextSquare.first][nextSquare.second] > 0) {
            int shipVal = shipLocations[nextSquare.first][nextSquare.second];
            hitLogic(nextSquare, shipLocations, shipVal);
        } else {
            removeShips(nextSquare);
            shipLocations[nextSquare.first][nextSquare.second] -= 100;
            boardStates.emplace_back(shipLocations);
        }
        fillProbBoard(potentialShips);
    }
    return boardStates;
}

