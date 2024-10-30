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
  Material(ReflectionType reflectionType, Color color,
           float diffuseReflexionCoef, float specularReflexionCoef)
      : reflectionType(reflectionType),
        color(color),
        diffuseReflexionCoef(diffuseReflexionCoef),
        specularReflexionCoef(specularReflexionCoef) {}
  Material() {
    reflectionType = ReflectionType::MAT;
    color = Color(1, 1, 1);
    diffuseReflexionCoef = 0.5f;
    specularReflexionCoef = 0.8f;
  }
  Material(ReflectionType reflectionType, Color color)
      : reflectionType(reflectionType), color(color) {
    diffuseReflexionCoef = 0.5f;
    specularReflexionCoef = 0.8f;
  }
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