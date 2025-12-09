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
  int totalWidth, totalHeight, boardWidth, boardHeight, boardMines;
public:
  vector<vector<std::unique_ptr<Tile>>> board;

  Board(Shader& shader);

  /// @brief Destroy the Square object and delete it's VAO and VBO
  ~Board();

  /// @brief Binds the VAO and calls the virtual draw function
  void setUniformsAndDraw() const;

  int getTotalMines(vector<vector<std::unique_ptr<Tile>>> &board) const;

  int getMaxMinesAllowed(vector<vector<std::unique_ptr<Tile>>> &board) const;

  void placeRandomMines(vector<vector<std::unique_ptr<Tile>>> &board, int &numleft) ;

  void clearPoint(vector<vector<std::unique_ptr<Tile>>> &board, int &posx, int &posy);

  int getNumMinesPoint(vector<vector<std::unique_ptr<Tile>>> &board, int &x, int &y) const;

  void openBoardPosition(vector<vector<int>> &points, vector<vector<std::unique_ptr<Tile>>> &board, vector<vector<std::unique_ptr<Tile>>> &dispBoard, int x, int y);

  vector<vector<int>> getMinesAtPoint(vector<vector<std::unique_ptr<Tile>>> &board, int x, int y);

  vector<vector<int>> getAvailablePoints(vector<vector<std::unique_ptr<Tile>>> &board, int x, int y);

  void generateBoard(int &startx, int &starty);

  void tileLeftClick(const vec2 &point);

  bool tileClicked(const vec2 &point);

  void uncoverTile(int x, int y);

  vector<vector<int>> showVals();

  void setSurroundingBombs();
};
#endif //BOARD_H

