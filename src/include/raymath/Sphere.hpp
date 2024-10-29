#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Sphere : public Shape, public Material {
 private:
  float radius;
  bool isVisible(Ray ray, Vector cameraSphereDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const override;

 public:
  Sphere(Vector position, float radius, ReflectionType reflectionType,
         Color color);
  Sphere(Vector position, float scale, float radius,
         ReflectionType reflectionType, Color color);
  ~Sphere() override = default;

  std::optional<Vector> getIntersectPoint(Ray ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere);
};