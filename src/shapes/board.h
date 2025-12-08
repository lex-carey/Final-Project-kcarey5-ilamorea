//
// Created by ibot6 on 12/4/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "../shader/shader.h"

class Board {
private:
  int totalWidth, totalHeight, boardWidth, boardHeight, boardMines;
  std::unique_ptr<vector<vector<Tile>>> board;
public:
  Board(Shader& shader);

  /// @brief Destroy the Square object and delete it's VAO and VBO
  ~Board();

  /// @brief Binds the VAO and calls the virtual draw function
  void setUniformsAndDraw() const;

  int getTotalMines(std::unique_ptr<vector<vector<Tile>>> &board) const;

  int getMaxMinesAllowed(std::unique_ptr<vector<vector<Tile>>> &board) const;

  void placeRandomMines(std::unique_ptr<vector<vector<Tile>>> &board, int &numleft);

  void clearPoint(std::unique_ptr<vector<vector<Tile>>> &board, int &posx, int &posy);

  int getNumMinesPoint(std::unique_ptr<vector<vector<Tile>>> &board, int &x, int &y) const;

  void openBoardPosition(vector<vector<int>> &points, std::unique_ptr<vector<vector<Tile>>> &board, std::unique_ptr<vector<vector<Tile>>> &dispBoard, int x, int y);

  vector<vector<int>> getMinesAtPoint(std::unique_ptr<vector<vector<Tile>>> &board, int x, int y);

  vector<vector<int>> getAvailablePoints(std::unique_ptr<vector<vector<Tile>>> &board, int &x, int &y);

  void generateBoard(int &startx, int &starty);

  void setSurroundingBombs();
};
#endif //BOARD_H

