#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

class ShaderPhong : public Shader {
 public:
  Color calculateShader(
      Color pixel,
      std::optional<Shape::IntersectionResult> intersectionResultOpt, Ray ray,
      const Shape& shape, Light light,
      const std::vector<std::unique_ptr<Shape>>& objects) const override;
};
