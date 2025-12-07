#include "board.h"


Board::Board(Shader& shader) {
    while (board->size() < 30) {
        totalWidth = 0;
        while (totalWidth < 660) {
            totalHeight = 0;
            vector<Tile> tiles;
            while (totalHeight < 352) {
                tiles.push_back(Tile(shader, vec2(71 + totalWidth + 10, 196 + totalHeight + 10), vec2(20, 20), color(154/255.0, 154/255.0, 154/255.0, 1)));
                totalHeight += 22;
            }
            board->push_back(tiles);
            totalWidth += 22;
        }
    }
}

Board::~Board() {
    for (vector<Tile> &tiles : board) {
        for (int i = 0; i < tiles.size(); i++) {
            tiles[i].~Tile();
        }
    }
}

void Board::setUniformsAndDraw() const {
    for (const std::unique_ptr<vector<Tile>> &tiles : board) {
        for (const std::unique_ptr<Tile> &tile : tiles) {
            tile->setUniforms();
            tile->draw();
        }
    }
}

Tile Board::getTile(int& x, int& y) {
    return board[x][y];
}

