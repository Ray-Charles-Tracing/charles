#pragma once

#include <string>
#include <vector>

#include "Color.hpp"
#include "MaterialType.hpp"
#include "Ray.hpp"
#include "ReflectionType.hpp"
#include "Shape.hpp"
#include "Triangle.hpp"
#include "Vector.hpp"

class Cube : public Shape {
 private:
  std::vector<Triangle> triangles;  // List of triangles representing cube faces

 public:
  // Constructor to create a cube from center, size, color, and material type
  Cube(Vector center, float size, Color color, ReflectionType reflectionType,
       MaterialType materialType);

  // Method to get intersection results with the ray
  std::optional<Shape::IntersectionResult> getIntersectResult(
      Ray ray) const override;
  bool isVisible(Ray ray, Vector cameraShapeDirection) const override;
  bool isIntersect(float centerToTheoricIntersectPointLength) const;

  std::string getType() const override { return "Cube"; }
};