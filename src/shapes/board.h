//
// Created by ibot6 on 12/4/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "../shader/shader.h"
#include <memory>
class Board {
private:
  int totalWidth, totalHeight;
public:
  std::unique_ptr<vector<vector<Tile>>> board;
  Board(Shader& shader);

  /// @brief Destroy the Square object and delete it's VAO and VBO
  ~Board();

  /// @brief Binds the VAO and calls the virtual draw function
  void setUniformsAndDraw() const;

  Tile getTile(int &x, int &y);

};
#endif //BOARD_H
