#pragma once

#include <optional>

#include "Color.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Sphere.hpp"

class ShaderFlat : public Shader {
 public:
  Color calculateShader(Color pixel, std::optional<Vector> intersectionPoint,
                        Ray ray, Sphere sphere) const override;
};
