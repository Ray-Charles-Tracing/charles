#pragma once

#include <optional>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class ShaderDiffus : public Shader {
 public:
  Color calculateShader(
      Color pixel,
      std::optional<Shape::IntersectionResult> intersectionResultOpt, Ray ray,
      const Shape& shape, Light light,
      const std::vector<std::unique_ptr<Shape>>& objects) const override;
};
