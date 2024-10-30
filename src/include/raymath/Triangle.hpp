#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Triangle : public Shape {
 private:
  Vector a;
  Vector b;
  Vector c;
  bool isVisible(Ray ray, Vector cameraSphereDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const;

 public:
  Triangle(Vector a, Vector b, Vector c, ReflectionType reflectionType,
           Color color);
  Triangle(Vector a, Vector b, Vector c, float scale,
           ReflectionType reflectionType, Color color,
           float diffuseReflexionCoef, float specularReflexionCoef);
  ~Triangle() override = default;

  std::optional<Vector> getIntersectPoint(Ray ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream,
                                  Triangle const& triangle);
};