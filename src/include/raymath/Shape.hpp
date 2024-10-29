#pragma once

#include <iostream>
#include <optional>

#include "Material.hpp"
#include "Vector.hpp"

class Shape : public Material {
 protected:
  Vector position;
  float scale;
  virtual bool isVisible(Ray ray, Vector cameraSphereDirection) const = 0;

 public:
  Shape(Vector position, float scale, Color color,
        ReflectionType reflectionType)
      : position(position), scale(scale), Material(reflectionType, color) {}
  Shape(Vector position, Color color, ReflectionType reflectionType)
      : position(position), Material(reflectionType, color) {
    scale = 1;
  }
  virtual ~Shape() = default;

  Vector getPosition() const { return position; }

  float getScale() const { return scale; }

  virtual std::optional<Vector> getIntersectPoint(Ray ray) const = 0;

  friend std::ostream& operator<<(std::ostream& _stream, Shape const& shape) {
    _stream << "(Position: " << shape.position << ", Scale: " << shape.scale
            << ")" << ", Material: " << static_cast<Material const&>(shape);
    return _stream;
  }
};