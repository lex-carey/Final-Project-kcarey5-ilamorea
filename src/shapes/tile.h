#ifndef FINAL_PROJECT_TILE_H
#define FINAL_PROJECT_TILE_H

#include "rect.h"

class Tile : public Rect {
private:
    bool clicked, bomb, marked;
    int surrBombs;
public:
    //Constructor
    Tile(Shader& shader, vec2 pos, vec2 size, struct color color);

    //Destructor
    ~Tile();

    //Setters
    void setClicked(bool& clicked);
    void setBomb(bool& bomb);
    void setSurrBombs(int& surrBombs);

    //Getters
    bool getClicked() const;
    bool getBomb() const;
    int getSurrBombs() const;

    static bool isOverlapping(const Tile &t1, const Tile &t2);

    bool isOverlapping(const Rect& r) const override;
};


#endif //FINAL_PROJECT_TILE_H