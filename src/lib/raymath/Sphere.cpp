#include "../../include/raymath/Sphere.hpp"

#include <cmath>
#include <iostream>
#include <optional>

Sphere::Sphere(Vector position, float radius, ReflectionType reflectionType,
               Color color, MaterialType materialType)
    : Shape(position, color, reflectionType, materialType), radius(radius) {}

Sphere::Sphere(Vector position, float scale, float radius,
               ReflectionType reflectionType, Color color,
               MaterialType materialType)
    : Shape(position, scale, color, reflectionType, materialType),
      radius(radius) {}

std::optional<Shape::IntersectionResult> Sphere::getIntersectResult(
    Ray ray) const {
  Vector cameraSphereDirection = getPosition() - ray.getOrigin();
  if (!isVisible(ray, cameraSphereDirection)) {
    return std::nullopt;
  }

  float scalarProductOfCameraSphereDirectionToRay =
      cameraSphereDirection.computeScalable(ray.getDirection());
  Vector cameraSphereDirectionProjection =
      ray.getDirection() * scalarProductOfCameraSphereDirectionToRay;

  Vector theoricIntersectPoint =
      ray.getOrigin() + cameraSphereDirectionProjection;
  Vector centerToTheoricIntersectPointDirection =
      theoricIntersectPoint - getPosition();
  float centerToTheoricIntersectPointLength =
      centerToTheoricIntersectPointDirection.getNorm();

  if (!isIntersect(centerToTheoricIntersectPointLength)) {
    return std::nullopt;
  }

  float theoricIntersectPointToRealIntersectPointLength =
      std::sqrt((radius * radius) - (centerToTheoricIntersectPointLength *
                                     centerToTheoricIntersectPointLength));
  Vector theoricIntersectPointToRealIntersectPointDirection =
      ray.getDirection() *
      (-1 * theoricIntersectPointToRealIntersectPointLength);

  // Return the intersection point and the normal vector at the intersection
  Vector realIntersectPoint =
      theoricIntersectPoint +
      theoricIntersectPointToRealIntersectPointDirection;
  Vector centerToRealIntersectionPoint = realIntersectPoint - getPosition();
  Vector normalOnIntersectionPoint = centerToRealIntersectionPoint.normalize();

  return IntersectionResult{realIntersectPoint,
                            normalOnIntersectionPoint.normalize()};
}

bool Sphere::isVisible(Ray ray, Vector cameraSphereDirection) const {
  float scalarProduct =
      cameraSphereDirection.normalize().computeScalable(ray.getDirection());
  return scalarProduct > 0;
}

bool Sphere::isIntersect(float centerToTheoricIntersectPointLength) const {
  return centerToTheoricIntersectPointLength < radius;
}

std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere) {
  _stream << "Shape: " << static_cast<Shape const&>(sphere)
          << ", Radius: " << sphere.radius;
  return _stream;
}
