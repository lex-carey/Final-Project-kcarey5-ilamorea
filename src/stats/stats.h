#ifndef FINAL_PROJECT_STATS_H
#define FINAL_PROJECT_STATS_H

#include "game.h"

#include <vector>
#include <memory>

class Stats {
private:
    std::vector<std::unique_ptr<Game>> games;
    std::vector<std::unique_ptr<Game>> topGames;
    std::unique_ptr<Game> bestGame;
    int avgBombs, avgTime,  gamesWon, logic, misclick, miscount, chance;
public:
    //Constructor
    Stats();

    //Getters
    int getAvgBombs() const;
    int getAvgTime() const;
    int getGamesWon() const;
    int getGamesLost() const;
    int getLogic() const;
    int getMisclick() const;
    int getMiscount() const;
    int getChance() const;

    //Utility
    void calculateStats();
    void logGame(const std::unique_ptr<Game>& myGame);
};


#endif //FINAL_PROJECT_STATS_H