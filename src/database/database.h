#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

enum class IconColour {
    BLUE,
    RED,
    MAGENTA,
    GREEN,
    YELLOW,
    CYAN,
    WHITE
};

class DatabaseException {
private:
    std::string message;

public:
    DatabaseException(const std::string &errorMessage);
    std::string getMessage() const;
};

class Database {
private:
    std::vector<std::string> usernames;
    std::vector<std::string> passwords;
    std::vector<IconColour> iconColours;
    std::vector<int> totalWins;
    std::vector<int> totalLosses;
    std::vector<int> totalGames;
    std::vector<float> winRates;
    std::vector<float> hitPercentages;

    void addContentToFile();
    void wipeFile();
    int findUser(const std::string &username, const std::string &password);

public:
    Database();
    void load();
    void pushToFile();

    bool addBaseUser(const std::string &username, const std::string &password, enum IconColour iconColour);
    bool checkUser(const std::string &username, const std::string &password);

    bool changeUserIcon(const std::string &username, const std::string &password, enum IconColour iconColour);
    bool changeUserAllStats(const std::string &username, const std::string &password, const int totalWin, const int totalLoss, const int totalGame, const int hits, const int turns);

    int getUserTotalWins(const std::string &username, const std::string &password);
    int getUserTotalLosses(const std::string &username, const std::string &password);
    int getUserTotalGames(const std::string &username, const std::string &password);
    float getUserWinRate(const std::string &username, const std::string &password);
    float getUserHitPercentage(const std::string &username, const std::string &password);
    IconColour getUserIcon(const std::string &username, const std::string &password);
};

#endif // DATABASE_H