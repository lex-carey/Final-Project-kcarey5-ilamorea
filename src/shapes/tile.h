#ifndef FINAL_PROJECT_TILE_H
#define FINAL_PROJECT_TILE_H

#include "rect.h"

class Tile : public Rect {
private:
    bool clicked, marked;
    int surrBombs;
    enum class States {SAFE = -1, UNSET = 0, POSSIBLE_BOMB = 1, BOMB = 2} state;
public:
    //Constructor
    Tile(Shader& shader, vec2 pos, vec2 size, struct color color);

    //Destructor
    ~Tile();

    //Setters
    void setClicked(bool& clicked);
    void setState(int state);
    void setSurrBombs(int& surrBombs);

    //Getters
    bool getClicked() const;
    bool getBomb() const;
    int getSurrBombs() const;
    int getState() const;

    //TODO: figure out overlapping functions
};


#endif //FINAL_PROJECT_TILE_H