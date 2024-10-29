#pragma once

#include <iostream>

#include "Color.hpp"
#include "ReflectionType.hpp"

class Material {
 protected:
  ReflectionType reflectionType;
  Color color;

 public:
  Material(ReflectionType reflectionType, Color color)
      : reflectionType(reflectionType), color(color) {}
  virtual ~Material() = default;

  ReflectionType getReflectionType() const { return reflectionType; }
  Color getColor() const { return color; }

  friend std::ostream& operator<<(std::ostream& _stream,
                                  Material const& material) {
    _stream << "(ReflectionType: " << static_cast<int>(material.reflectionType)
            << ", Color: " << material.color << ")";
    return _stream;
  }
};