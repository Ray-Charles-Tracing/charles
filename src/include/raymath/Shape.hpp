#pragma once

#include <iostream>

#include "../raymath/Vector.hpp"

class Shape {
 protected:
  Vector position;
  float scale;

 public:
  Shape(Vector position, float scale) : position(position), scale(scale) {}
  virtual ~Shape() = default;

  Vector getPosition() const { return position; }

  float getScale() const { return scale; }

  virtual Vector intersect(Vector ray) const = 0;

  friend std::ostream& operator<<(std::ostream& _stream, Shape const& shape) {
    _stream << "Position: " << shape.position << ", Scale: " << shape.scale;
    return _stream;
  }
};