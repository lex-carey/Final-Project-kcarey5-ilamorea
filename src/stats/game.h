#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H


class Game {
private:
    int month, year, bombs, time;
    bool won;
    enum class Reasons {NOT_TRACKING, LOGIC, MISCLICK, MISCOUNT, CHANCE} reason;
public:
    //Constructors
    Game();
    Game(const int &month, const int &year, const int &bombs, const int &time, const int &reason, const int &won);

    //Setters
    void setDate(const int &month, const int &year);
    void setBombs(const int &bombs);
    void setTime(const int &time);
    void setReason(const int &reason);
    void setWon(const int &won);

    //Getters
    int getMonth() const;
    int getYear() const;
    int getBombs() const;
    int getTime() const;
    int getReason() const;
    int getWon() const;

    //Operators
    friend bool operator < (const Game &g1, const Game &g2) {
        bool less = false;
        if (g1.getTime() > g2.getTime()) {
            if (g1.getBombs() <= g2.getBombs()) {
                less = true;
            }
        }
        else if (g1.getBombs() < g2.getBombs()) {
            if (g1.getTime() >= g2.getTime()) {
                less = true;
            }
        }
        return less;
    }

    friend bool operator > (const Game &g1, const Game &g2) {
        bool greater = false;
        if (g1.getTime() < g2.getTime()) {
            if (g1.getBombs() >= g2.getBombs()) {
                greater = true;
            }
        }
        else if (g1.getBombs() > g2.getBombs()) {
            if (g1.getTime() <= g2.getTime()) {
                greater = true;
            }
        }
        return greater;
    }

    friend bool operator == (const Game &g1, const Game &g2) {
        return (g1.getTime() == g2.getTime() && g1.getBombs() != g2.getBombs());
    }

    friend bool operator != (const Game &g1, const Game &g2) {
        return (g1.getTime() != g2.getTime() || g1.getBombs() != g2.getBombs());
    }

    friend bool operator <= (const Game &g1, const Game &g2) {
        bool less = false;
        if (g1.getBombs() == g2.getBombs()) {
            if (g1.getTime() <= g2.getTime()) {
                less = false;
            }
        }
        else if (g1.getBombs() <= g2.getBombs()) less = true;
        return less;
    }

    friend bool operator >= (const Game &g1, const Game &g2) {
        bool greater = false;
        if (g1.getBombs() == g2.getBombs()) {
            if (g1.getTime() > g2.getTime()) greater = false;
            if (g1.getTime() < g2.getTime()) greater = true;
        }
        if (g1.getTime() == g2.getTime()) {
            if (g1.getBombs() > g2.getBombs()) greater = true;
            if (g1.getBombs() < g2.getBombs()) greater = false;
        }
        else if (g1.getBombs() >= g2.getBombs()) greater = true;
        return greater;
    }
};


#endif //FINAL_PROJECT_GAME_H