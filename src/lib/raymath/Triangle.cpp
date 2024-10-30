#include "../../include/raymath/Triangle.hpp"

#include <cmath>
#include <iostream>

Triangle::Triangle(Vector a, Vector b, Vector c, ReflectionType reflectionType,
                   Color color, MaterialType materialType)
    : Shape((a + b + c) / 3.0, color, reflectionType, materialType),
      a(a),
      b(b),
      c(c) {}

Triangle::Triangle(Vector a, Vector b, Vector c, float scale,
                   ReflectionType reflectionType, Color color,
                   MaterialType materialType)
    : Shape((a + b + c) / 3, scale, color, reflectionType, materialType),
      a(a),
      b(b),
      c(c) {}

std::optional<Shape::IntersectionResult> Triangle::getIntersectResult(
    Ray ray) const {
  // Find the theoretical intersect points?

  // Calculate the edges of the triangle
  Vector edge1 = b - a;
  Vector edge2 = c - a;

  // Calculate the vector perpendicular to the ray direction and edge2
  // ! Return the normalized vector perpendicular to the ray direction and edge2
  Vector h = ray.getDirection().cross(edge2);
  Vector normal = h.normalize();

  // Calculate the determinant to check if the ray intersects the triangle
  float aDet = edge1.computeScalable(h);

  // If the determinant is close to zero, the ray is parallel to the triangle
  if (fabs(aDet) < 1e-6)
    return std::nullopt;  // Ray is parallel to the triangle

  float f = 1.0 / aDet;
  Vector s = ray.getOrigin() - a;

  // Calculate barycentric coordinate u to check if the intersection is within
  // the triangle
  float u = f * s.computeScalable(h);
  if (u < 0.0 || u > 1.0) return std::nullopt;

  Vector q = s.cross(edge1);

  // Calculate barycentric coordinate v to check if the intersection is within
  // the triangle
  float v = f * ray.getDirection().computeScalable(q);
  if (v < 0.0 || u + v > 1.0) return std::nullopt;

  // Calculate t to determine the distance from the ray origin to the
  // intersection point
  float t = f * edge2.computeScalable(q);
  if (t > 1e-6) {  // Intersection point is on the ray
    Vector intersectPoint = ray.getOrigin() + ray.getDirection() * t;
    return IntersectionResult{intersectPoint, normal};
  } else {
    return std::nullopt;  // No intersection
  }
}

// ! A implémenter dans la méthode getIntersectResult
bool Triangle::isVisible(Ray ray, Vector cameraTriangleDirection) const {
  // Basic visibility check, e.g., could return true if the triangle's normal
  // faces the camera or based on other visibility logic
  return true;
}

bool Triangle::isIntersect(float centerToTheoricIntersectPointLength) const {
  // Basic intersection check, e.g., could return true if the distance between
  // the sphere center and the theoretical intersection point is less than the
  // sphere's radius
  return true;
}

std::ostream& operator<<(std::ostream& _stream, Triangle const& triangle) {
  _stream << "Triangle: " << triangle.a << " " << triangle.b << " "
          << triangle.c << " " << triangle.getPosition() << " "
          << triangle.getColor();
  return _stream;
}
