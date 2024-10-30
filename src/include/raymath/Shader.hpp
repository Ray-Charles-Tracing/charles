#pragma once

#include <optional>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

class Shader {
 protected:
  std::tuple<Vector, Vector, Vector, Vector> getDiffuseBased(
      Vector intersectionPoint, Ray ray, const Shape& shape,
      Light light) const {
    Vector shapePos = shape.getPosition();
    Vector cp = intersectionPoint - shapePos;
    Vector normal = cp.normalize();

    Vector lightDir = (light.getPosition() - intersectionPoint).normalize();
    Vector viewDir = (ray.getOrigin() - intersectionPoint).normalize();

    return std::make_tuple(intersectionPoint, normal, lightDir, viewDir);
  }

 public:
  virtual Color calculateShader(Color pixel,
                                std::optional<Vector> intersectionPoint,
                                Ray ray, const Shape& shape,
                                Light light) const = 0;
  virtual ~Shader() = default;
};
