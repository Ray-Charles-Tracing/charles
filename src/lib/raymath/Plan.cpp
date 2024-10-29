#include "../include/raymath/Plan.hpp"

// Constructeur du plan avec normale définie
Plan::Plan(Vector position, Vector normal, ReflectionType reflectionType,
           Color color)
    : Shape(reflectionType, color),
      Material(reflectionType, color),
      normal(normal) {
  this->position = position;
}

// Constructeur du plan avec une normale par défaut
Plan::Plan(Vector position, ReflectionType reflectionType, Color color)
    : Shape(reflectionType, color),
      Material(reflectionType, color),
      normal(Vector(0, 0, 1)) {
  this->position = position;
}

// Calcule le point d'intersection entre le rayon et le plan
std::optional<Vector> Plan::getIntersectPoint(Ray ray) const {
  Vector rayDirection = ray.getDirection();
  Vector rayOrigin = ray.getOrigin();

  // Calcul du produit scalaire entre la normale et la direction du rayon
  float denominator = normal.computeScalable(rayDirection);

  // Si le produit scalaire est nul, le rayon est parallèle au plan
  if (denominator == 0) {
    return std::nullopt;
  }

  // Calcul de la distance t au point d'intersection
  Vector aMinusRayOrigin = position - rayOrigin;
  float t = normal.computeScalable(aMinusRayOrigin) / denominator;

  // Si t est négatif, l'intersection est derrière le rayon
  if (t < 0) {
    return std::nullopt;
  }

  // Retourne le point d'intersection
  return rayOrigin + rayDirection * t;
}

// Surcharge de l'opérateur pour afficher les informations du plan
std::ostream& operator<<(std::ostream& _stream, Plan const& plan) {
  _stream << "Plan(Position: " << plan.position << ", Normal: " << plan.normal
          << ", ReflectionType: " << plan.reflectionType
          << ", Color: " << plan.color << ")";
  return _stream;
}