#include "../../include/raymath/Plan.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

Plan::Plan(Vector position, Vector normal, ReflectionType reflectionType,
           Color color)
    : Shape(position, reflectionType, color), normal(normal) {}

Plan::Plan(Vector position, ReflectionType reflectionType, Color color)
    : Shape(position, reflectionType, color), normal(Vector(0, 1, 0)) {}

bool Plan::isVisible(Ray ray, Vector cameraPlanDirection) const {
  float cameraPlanDirectionNorm = cameraPlanDirection.getNorm();

  Vector cameraPlanDirectionNormalized = cameraPlanDirection.normalize();

  float scalarProduct =
      cameraPlanDirectionNormalized.computeScalable(ray.getDirection());

  if (scalarProduct > 0) {
    return true;
  }
  return false;
}

bool Plan::isIntersect(float centerToTheoricIntersectPointLength) const {
  // TODOREVIEW SA : Vérifier si le plan est bien intersecté
  return true;
}

std::optional<Vector> Plan::getIntersectPoint(Ray ray) const {
  Vector cameraPlanDirection = getPosition() - ray.getOrigin();

  if (isVisible(ray, cameraPlanDirection) == false) {
    return std::nullopt;
  }
}

std::ostream& operator<<(std::ostream& _stream, Plan const& plan) {
  _stream << "Plan(Position: " << plan.position << ", Normal: " << plan.normal
          << ", ReflectionType: " << plan.reflectionType
          << ", Color: " << plan.color << ")";
  return _stream;
}