#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "MaterialType.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Sphere : public Shape {
 private:
  float radius;
  bool isVisible(Ray ray, Vector cameraShapeDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const;

 public:
  Sphere(Vector position, float radius, ReflectionType reflectionType,
         Color color, MaterialType materialType);

  Sphere(Vector position, float scale, float radius,
         ReflectionType reflectionType, Color color, MaterialType materialType);

  ~Sphere() override = default;

  std::optional<IntersectionResult> getIntersectResult(Ray ray) const override;

  std::string toObjData(int& vertexIndex) const override;

  std::string toObjData(int& vertexIndex) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere);
};
