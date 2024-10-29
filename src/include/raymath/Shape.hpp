#pragma once

#include <iostream>
#include <optional>

#include "Vector.hpp"

class Shape {
 protected:
  Vector position;
  float scale = 1;
  virtual bool isVisible(Ray ray, Vector cameraSphereDirection) const = 0;
  virtual bool isIntersect(float centerToTheoricIntersectPointLength) const = 0;

 public:
  Shape(Vector position, float scale) : position(position), scale(scale) {}
  Shape(Vector position) : position(position) {}
  virtual ~Shape() = default;

  Vector getPosition() const { return position; }

  float getScale() const { return scale; }

  virtual std::optional<Vector> getIntersectPoint(Ray ray) const = 0;

  friend std::ostream& operator<<(std::ostream& _stream, Shape const& shape) {
    _stream << "(Position: " << shape.position << ", Scale: " << shape.scale
            << ")";
    return _stream;
  }
};