#include "tile.h"


Tile::Tile(Shader& shader, vec2 pos, vec2 size, struct color color) : Rect(shader, pos, size, color) {
    clicked = marked = false;
    surrBombs = 0;
    state = States::UNSET;
}

Tile::~Tile() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Tile::setClicked(bool& clicked) {
    this->clicked = clicked;
}

void Tile::setState(int state) {
    this->state = static_cast<States>(state);
}

void Tile::setSurrBombs(int& surrBombs) {
    this->surrBombs = surrBombs;
}

bool Tile::getClicked() const {
    return clicked;
}

bool Tile::getBomb() const {
    return state == States::BOMB;
}

int Tile::getSurrBombs() const {
    return surrBombs;
}

int Tile::getState() const {
    return static_cast<int>(state);
}
