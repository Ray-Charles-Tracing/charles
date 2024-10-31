#include "../../include/raymath/Cube.hpp"

#include <limits>  // For std::numeric_limits

Cube::Cube(Vector center, float size, Color color,
           ReflectionType reflectionType, MaterialType materialType)
    : Shape(center, color, reflectionType, materialType) {
  // Calculate half the size for easy corner positioning
  float halfSize = size / 2;

  // Define each corner of the cube based on the center and size
  Vector v0 = center + Vector(-halfSize, -halfSize, halfSize);
  Vector v1 = center + Vector(halfSize, -halfSize, halfSize);
  Vector v2 = center + Vector(halfSize, halfSize, halfSize);
  Vector v3 = center + Vector(-halfSize, halfSize, halfSize);
  Vector v4 = center + Vector(-halfSize, -halfSize, -halfSize);
  Vector v5 = center + Vector(halfSize, -halfSize, -halfSize);
  Vector v6 = center + Vector(halfSize, halfSize, -halfSize);
  Vector v7 = center + Vector(-halfSize, halfSize, -halfSize);

  // Add two triangles per face of the cube to form six faces in total

  // Front face
  triangles.push_back(
      Triangle(v1, v0, v3, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v3, v2, v1, reflectionType, color, materialType));

  // Right face
  triangles.push_back(
      Triangle(v2, v6, v5, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v5, v1, v2, reflectionType, color, materialType));

  // Back face
  triangles.push_back(
      Triangle(v5, v4, v7, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v7, v6, v5, reflectionType, color, materialType));

  // Left face
  triangles.push_back(
      Triangle(v3, v7, v4, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v4, v0, v3, reflectionType, color, materialType));

  // Top face
  triangles.push_back(
      Triangle(v2, v3, v7, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v7, v6, v2, reflectionType, color, materialType));

  // Bottom face
  triangles.push_back(
      Triangle(v4, v5, v1, reflectionType, color, materialType));
  triangles.push_back(
      Triangle(v1, v0, v4, reflectionType, color, materialType));
}

std::optional<Shape::IntersectionResult> Cube::getIntersectResult(
    Ray ray) const {
  // Initialize variables to keep track of the closest intersection
  std::optional<Shape::IntersectionResult> closestIntersection = std::nullopt;
  float minDistance =
      std::numeric_limits<float>::max();  // Start with max distance

  // Loop through each triangle in the cube
  for (const auto& triangle : triangles) {
    // Get intersection result for the current triangle
    auto intersectResult = triangle.getIntersectResult(ray);

    // If an intersection is found
    if (intersectResult) {
      // std::cout << "intersectResult: " << intersectResult->intersectPoint
      //           << std::endl;
      // Calculate the distance from ray origin to intersection point
      float distance =
          (intersectResult->intersectPoint - ray.getOrigin()).getNorm();

      // Check if the intersection is in front of the ray
      if (distance < minDistance &&
          distance > 0) {  // Ensure distance is positive
        minDistance = distance;
        closestIntersection = intersectResult;  // Update closest intersection
      }
    }
  }

  // Return the closest intersection result (if any), or std::nullopt if none
  return closestIntersection;
}

bool Cube::isVisible(Ray ray, Vector cameraShapeDirection) const {
  // Check if the cube is visible from the camera
  // for (const auto& triangle : triangles) {
  //   if (triangle.isVisible(ray, cameraShapeDirection)) {
  //     return true;
  //   }
  // }
  // return false;
}

bool Cube::isIntersect(float centerToTheoricIntersectPointLength) const {
  // Check if the cube intersects with the ray
  // return centerToTheoricIntersectPointLength < 0.5f;
}
