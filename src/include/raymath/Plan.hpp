#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Plan : public Shape, public Material {
 private:
  Vector normal;

 public:
  Plan(Vector position, Vector normal, ReflectionType reflectionType,
       Color color);
  Plan(Vector position, ReflectionType reflectionType, Color color);
  ~Plan() override = default;

  std::optional<Vector> getIntersectPoint(Ray ray) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Plan const& plan);
};
