#pragma once

#include <optional>

#include "Color.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

class Shader {
 public:
  virtual Color calculateShader(Color pixel,
                                std::optional<Vector> inetersectionPoint,
                                Ray ray, Sphere sphere) const = 0;
  virtual ~Shader() = default;
};
