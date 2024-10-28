#pragma once

#include "Color.hpp"
#include "Material.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Sphere : public Shape, public Material {
 private:
  float radius;

 public:
  Sphere(Vector position, float radius, ReflectionType reflectionType,
         Color color);
  Sphere(Vector position, float scale, float radius,
         ReflectionType reflectionType, Color color);
  ~Sphere() override = default;

  Vector intersect(Vector const& ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere);
};