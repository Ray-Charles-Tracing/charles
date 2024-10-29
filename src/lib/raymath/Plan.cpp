#include "../include/raymath/Plan.hpp"

Plan::Plan(Vector position, ReflectionType reflectionType, Color color)
    : Shape(reflectionType, color), Material(reflectionType, color) {
  this->position = position;
  this->normal = Vector(0, 0, 1);
}

Plan::Plan(Vector position, float scale, ReflectionType reflectionType,
           Color color)
    : Shape(reflectionType, color), Material(reflectionType, color) {
  this->position = position;
  this->normal = Vector(0, 0, 1) * scale;
}

Plan::~Plan() {}

std::optional<Vector> Plan::getIntersectPoint(Ray ray) const {
  Vector rayDirection = ray.getDirection();
  Vector rayOrigin = ray.getOrigin();
  float denominator = normal.computeScalable(rayDirection);

  if (denominator == 0) {
    return std::nullopt;
  }

  Vector aMinusRayOrigin = position - rayOrigin;
  float t = normal.computeScalable(aMinusRayOrigin) / denominator;

  if (t < 0) {
    return std::nullopt;
  }

  return rayOrigin + rayDirection * t;
}

bool Plan::isVisible(Ray ray, Vector cameraPlanDirection) const {
  // Vérifier si le plan est orienté vers la caméra
  float dotProduct = normal.computeScalable(cameraPlanDirection);
  return dotProduct <
         0;  // Le plan est visible si le produit scalaire est négatif
}

bool Plan::isIntersect(float centerToTheoricIntersectPointLength) const {
  return centerToTheoricIntersectPointLength < 0;
}

bool Plan::operator==(Plan const& plan) const {
  return position == plan.position && reflectionType == plan.reflectionType &&
         color == plan.color;
}

std::ostream& operator<<(std::ostream& _stream, Plan const& plan) {
  _stream << "Plan(Position: " << plan.position
          << ", ReflectionType: " << plan.reflectionType
          << ", Color: " << plan.color << ")";
  return _stream;
}