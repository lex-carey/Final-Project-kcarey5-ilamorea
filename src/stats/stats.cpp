#include "stats.h"

#include <fstream>


Stats::Stats() {
    //Initializing games
    std::ifstream log("../res/logs/games.csv");
    if (log) {
        int month, year, score, time, reason, won;
        char comma;
        while (log) {
            log >> month;
            log >> comma;

            log >> year;
            log >> comma;

            log >> score;
            log >> comma;

            log >> time;
            log >> comma;

            log >> reason;
            log >> comma;

            log >> won;
            log >> std::ws;

            games.push_back(std::make_unique<Game>(month, year, score, time, reason, won));

            if (log.peek() == EOF) log.close();
        }
    }
    //Initializing topGames
    std::ifstream topLog("../res/logs/topGames.csv");
    if (topLog) {
        int month, year, score, time, reason, won;
        char comma;
        while (topLog)
        {
            topLog >> month;
            topLog >> comma;

            topLog >> year;
            topLog >> comma;

            topLog >> score;
            topLog >> comma;

            topLog >> time;
            topLog >> comma;

            topLog >> reason;
            topLog >> comma;

            topLog >> won;
            topLog >> std::ws;

            topGames.push_back(std::make_unique<Game>(month, year, score, time, reason, won));

            if (topLog.peek() == EOF) topLog.close();
        }
    }
    //Initializing bestGame
    bestGame = std::make_unique<Game>(*topGames.back());
    //Initializing avgBombs, avgTime, gamesWon, logic, misclick, miscount, chance
    avgBombs = avgTime = gamesWon = logic = misclick = miscount = chance = 0;
    calculateStats();
}

void Stats::calculateStats() {
    if (!games.empty()) {
        for (const auto& game : games) {
            avgBombs += game->getBombs();
            avgTime += game->getTime();
            switch (game->getReason()) {
                case 1:
                    logic++;
                    break;
                case 2:
                    misclick++;
                    break;
                case 3:
                    miscount++;
                    break;
                case 4:
                    chance++;
                    break;
                default: break;
            }
            if (game->getWon()) gamesWon++;
        }
        avgBombs = avgBombs/games.size();
        avgTime = avgTime/games.size();
    }
}

void Stats::logGame(const std::unique_ptr<Game>& myGame) {
    //updating game log
    games.push_back(std::make_unique<Game>(*myGame));
    std::ofstream updatedLog("../res/logs/games.csv");
    for (const std::unique_ptr<Game> &game : games) {
        updatedLog << game->getMonth() << "," << game->getYear() << "," << game->getBombs() << ","
        << game->getTime() << "," << game->getReason() << "," << game->getWon() << "\n";
    }
    updatedLog.close();
    //game will be put in topGames vector (and subsequently topGames.csv) if there are no top games yet
    if (topGames.empty()) {
        topGames.push_back(std::make_unique<Game>(*myGame));
        std::ofstream fileOut("../res/logs/topGames.csv");
        for (const std::unique_ptr<Game> &game : topGames){
            fileOut << game->getMonth() << "," << game->getYear() << "," << game->getBombs() << ","
            << game->getTime() << "," << game->getReason() << "," << game->getWon() << "\n";
        }
        fileOut.close();
    }
    //created game is compared to the last game entered into topGames vector, as this will be the current best game. If new game is better, it is added to topGames and subsequently topGames.csv
    else {
        if (*myGame >= *topGames.back()) {
            topGames.push_back(std::make_unique<Game>(*myGame));
            std::ofstream fileOut("../res/logs/topGames.csv");
            for (const std::unique_ptr<Game> &topGame : topGames) {
                fileOut << topGame->getMonth() << "," << topGame->getYear() << "," << topGame->getBombs() << ","
                << topGame->getTime() << "," << topGame->getReason() << "," << topGame->getWon() << "\n";
            }
            fileOut.close();
        }
    }
}

int Stats::getAvgBombs() const {
    return avgBombs;
}

int Stats::getAvgTime() const {
    return avgTime;
}

int Stats::getGamesWon() const {
    return gamesWon;
}

int Stats::getGamesLost() const {
    return games.size() - gamesWon;
}

int Stats::getLogic() const {
    return logic;
}

int Stats::getMisclick() const {
    return misclick;
}

int Stats::getMiscount() const {
    return miscount;
}

int Stats::getChance() const {
    return chance;
}
