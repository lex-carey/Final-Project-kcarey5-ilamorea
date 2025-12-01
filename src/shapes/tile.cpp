#include "tile.h"


Tile::Tile(Shader& shader, vec2 pos, vec2 size, struct color color) : Rect(shader, pos, size, color) {
    clicked = bomb = false;
    surrBombs = 0;
}

Tile::~Tile() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Tile::setClicked(bool& clicked) {
    this->clicked = clicked;
}

void Tile::setBomb(bool& bomb) {
    this->bomb = bomb;
}

void Tile::setSurrBombs(int& surrBombs) {
    this->surrBombs = surrBombs;
}

bool Tile::getClicked() const {
    return clicked;
}

bool Tile::getBomb() const {
    return bomb;
}

int Tile::getSurrBombs() const {
    return surrBombs;
}
