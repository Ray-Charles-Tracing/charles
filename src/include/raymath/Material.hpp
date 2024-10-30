#pragma once

#include <iostream>

#include "Color.hpp"
#include "ReflectionType.hpp"

class Material {
 protected:
  ReflectionType reflectionType;
  Color color;
  float diffuseReflexionCoef;
  float specularReflexionCoef;

 public:
  Material(ReflectionType reflectionType = ReflectionType::MAT,
           Color color = Color(1, 1, 1), float diffuseReflexionCoef = 0.5f,
           float specularReflexionCoef = 0.8f)
      : reflectionType(reflectionType),
        color(color),
        diffuseReflexionCoef(diffuseReflexionCoef),
        specularReflexionCoef(specularReflexionCoef) {}
  virtual ~Material() = default;

  ReflectionType getReflectionType() const { return reflectionType; }
  Color getColor() const { return color; }
  float getDiffuseReflexionCoef() const { return diffuseReflexionCoef; }
  float getSpecularReflexionCoef() const { return specularReflexionCoef; }

  friend std::ostream& operator<<(std::ostream& _stream,
                                  Material const& material) {
    _stream << "(ReflectionType: " << static_cast<int>(material.reflectionType)
            << ", Color: " << material.color
            << ", K_D: " << material.diffuseReflexionCoef
            << ", K_S: " << material.specularReflexionCoef << ")";
    return _stream;
  }
};