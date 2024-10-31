#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "MaterialType.hpp"
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
  bool isIntersect(Vector intersection, Vector a, Vector b, Vector c) const;

 public:
  Triangle(Vector a, Vector b, Vector c, ReflectionType reflectionType,
           Color color, MaterialType materialType);
  Triangle(Vector a, Vector b, Vector c, float scale,
           ReflectionType reflectionType, Color color,
           MaterialType materialType);
  ~Triangle() override = default;

  std::optional<IntersectionResult> getIntersectResult(Ray ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream,
                                  Triangle const& triangle);
};