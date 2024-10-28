#pragma once

#include "Color.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"

class Shader {
 public:
  virtual Color calculateShader(Color pixel, Ray ray, Sphere sphere) const = 0;
  virtual ~Shader() = default;
};
