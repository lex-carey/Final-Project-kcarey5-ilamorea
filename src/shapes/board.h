//
// Created by ibot6 on 12/4/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "rect.h"
#include "../shader/shader.h"

class Board : public Rect{
  private:
private:
  /// @brief Initializes the vertices and indices of the square
  void initVectors();
//NOTE/TODO: We probably want to override a fair chunk of the rect functions. Not sure which ones exactly? Maybe less of these than
//I have declared here.
public:
  /// @brief Construct a new Square object
  /// @details This constructor will call the InitRenderData function.
  /// @param shader The shader to use
  /// @param pos The position of the square
  /// @param size The size of the square
  /// @param color The color of the square
  Board(Shader & shader, vec2 pos, vec2 size, struct color color);

  Board(Board const& other);

  /// @brief Destroy the Square object and delete it's VAO and VBO
  ~Board();

  /// @brief Binds the VAO and calls the virtual draw function
  void draw() const override;

  float getLeft() const override;
  float getRight() const override;
  float getTop() const override;
  float getBottom() const override;

  static bool isOverlapping(const Rect& r1, const Rect& r2);
  bool isOverlapping(const Rect& other) const;
  bool isOverlapping(const Shape& other) const override;

};
#endif //BOARD_H
