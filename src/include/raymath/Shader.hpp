#pragma once

#include <optional>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

class Shader {
 public:
  virtual Color calculateShader(Color pixel,
                                std::optional<Vector> intersectionPoint,
                                Ray ray, const Shape& shape,
                                Light light) const = 0;
  virtual ~Shader() = default;
};
