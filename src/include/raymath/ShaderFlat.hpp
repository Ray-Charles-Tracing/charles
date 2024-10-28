#pragma once

#include "Color.hpp"
#include "Ray.hpp"
#include "Shader.hpp"
#include "Sphere.hpp"

class ShaderFlat : public Shader {
 public:
  Color calculateShader(Color pixel, Ray ray, Sphere sphere) const override;
};
