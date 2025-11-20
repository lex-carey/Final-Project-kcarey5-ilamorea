#include "game.h"


Game::Game() {
    month = year = bombs = time = 0;
    reason = Reasons::NOT_TRACKING;
    won = false;
}

Game::Game(const int& month, const int& year, const int& bombs, const int& time, const int& reason, const int& won) {
    this->month = month;
    this->year = year;
    this->bombs = bombs;
    this->time = time;
    this->reason = static_cast<Reasons>(reason);
    this->won = static_cast<bool>(won);
}

void Game::setDate(const int& month, const int& year) {
    this->month = month;
    this->year = year;
}

void Game::setBombs(const int& bombs) {
    this->bombs = bombs;
}

void Game::setTime(const int& time) {
    this->time = time;
}

void Game::setReason(const int& reason) {
    this->reason = static_cast<Reasons>(reason);
}

void Game::setWon(const int& won) {
    this->won = static_cast<bool>(won);
}

int Game::getMonth() const {
    return month;
}

int Game::getYear() const {
    return year;
}

int Game::getBombs() const {
    return bombs;
}

int Game::getTime() const {
    return time;
}

int Game::getReason() const {
    switch (reason) {
    case Reasons::NOT_TRACKING:
        return 0;
    case Reasons::LOGIC:
        return 1;
    case Reasons::MISCLICK:
        return 2;
    case Reasons::MISCOUNT:
        return 3;
    case Reasons::CHANCE:
        return 4;
    }
}

int Game::getWon() const {
    return won;
}




