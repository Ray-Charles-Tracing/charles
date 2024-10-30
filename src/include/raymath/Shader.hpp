#pragma once

#include <cmath>
#include <memory>
#include <optional>
#include <vector>

#include "Color.hpp"
#include "Light.hpp"
#include "Ray.hpp"
#include "Shape.hpp"
#include "Sphere.hpp"
#include "Vector.hpp"

class Shader {
 protected:
  std::tuple<Vector, Vector, Vector, Vector> getDiffuseBases(
      Vector intersectionPoint, Ray ray, const Shape& shape,
      Light light) const {
    Vector shapePos = shape.getPosition();
    Vector cp = intersectionPoint - shapePos;
    Vector normal = cp.normalize();
    Vector lightDir = (light.getPosition() - intersectionPoint).normalize();
    Vector viewDir = (ray.getOrigin() - intersectionPoint).normalize();

    return std::make_tuple(intersectionPoint, normal, lightDir, viewDir);
  }

  std::tuple<float, Color> getSpeculareBases(Vector lightDir, Vector normal,
                                             const Shape& shape, Vector viewDir,
                                             Color lightColor,
                                             Light light) const {
    Vector reflection =
        (normal * (2 * normal.computeScalable(lightDir)) - lightDir)
            .normalize();

    float k_s = shape.getSpecularReflexionCoef();
    float alpha = light.getShiningCoef();

    float diffuseIntensity = std::max(0.0f, normal.computeScalable(lightDir));
    float specularIntensity =
        std::pow(std::max(0.0f, reflection.computeScalable(viewDir)), alpha);
    Color specularColor =
        Color(1.0f, 1.0f, 1.0f) * k_s * specularIntensity * lightColor;

    return std::make_tuple(diffuseIntensity, specularColor);
  }

 public:
  virtual Color calculateShader(
      Color pixel, std::optional<Vector> intersectionPoint, Ray ray,
      const Shape& shape, Light light,
      const std::vector<std::unique_ptr<Shape>>& objects) const = 0;
  virtual ~Shader() = default;
};
