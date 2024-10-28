#pragma once

#include <iostream>

#include "Vector.hpp"

class Shape {
 protected:
  Vector position;
  float scale = 1;

 public:
  Shape(Vector position, float scale) : position(position), scale(scale) {}
  Shape(Vector position) : position(position) {}
  virtual ~Shape() = default;

  Vector getPosition() const { return position; }

  float getScale() const { return scale; }

  virtual Vector intersect(Vector ray) const = 0;

  friend std::ostream& operator<<(std::ostream& _stream, Shape const& shape) {
    _stream << "Position: " << shape.position << ", Scale: " << shape.scale;
    return _stream;
  }
};