#pragma once

#include <iostream>
#include <optional>

#include "Color.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Vector.hpp"

class Plan : public Shape {
 private:
  Vector normal;
  bool isVisible(Ray ray, Vector cameraShapeDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const;

 public:
  Plan(Vector position, Vector normal, ReflectionType reflectionType,
       Color color, MaterialType materialType);
  Plan(Vector position, float scale, Vector normal,
       ReflectionType reflectionType, Color color, MaterialType materialType);
  ~Plan() override = default;

  std::optional<IntersectionResult> getIntersectResult(Ray ray) const override;

  std::string toObjData(int& vertexIndex) const override;

  std::string toObjData(int& vertexIndex) const override;

  friend std::ostream& operator<<(std::ostream& _stream, Plan const& plan);
};