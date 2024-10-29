#pragma once

#include <optional>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

class ShaderPecular : public Shader {
 public:
  Color calculateShader(Color pixel, std::optional<Vector> intersectionPoint,
                        Ray ray, Sphere sphere, Light light) const override;
};
