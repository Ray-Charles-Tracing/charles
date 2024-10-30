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

bool Plan::isVisible(Ray ray, Vector cameraPlanDirection) const { return true; }

bool Plan::isIntersect(float centerToTheoricIntersectPointLength) const {
  // TODOREVIEW SA : Vérifier si le plan est bien intersecté
  return true;
}

std::optional<Vector> Plan::getIntersectPoint(Ray ray) const {
  // Vérifier si le plan est parralele au rayon ou derrière la caméra
  float dotProductBetweenRayAndNormal =
      ray.getDirection().computeScalable(normal);

  if (dotProductBetweenRayAndNormal >= 0) {
    return std::nullopt;
  }

  // Calculer le déplacement entre l'origine de la caméra et l'origine du plan
  Vector cameraPlanDirection = getPosition() - ray.getOrigin();

  // Calculer le produit scalaire entre le Vecteur Oc et la normale du plan
  float dotProductBetweenCameraPlanDirectionAndRay =
      cameraPlanDirection.computeScalable(ray.getDirection());

  // Calculer le multiplicateur du rayon normalisé pour atteindre le point
  // d'intersection Vector t
  float tCoeff = dotProductBetweenCameraPlanDirectionAndRay /
                 dotProductBetweenRayAndNormal;

  // Calculer le point d'intersection réel
  Vector cameraToTheoryIntersectPoint = ray.getDirection() * tCoeff;

  Vector realIntersectPoint = ray.getOrigin() + cameraToTheoryIntersectPoint;

  // Retourner le point d'intersection réel
  return realIntersectPoint;
}

std::ostream& operator<<(std::ostream& _stream, Plan const& plan) {
  _stream << "Plan(Position: " << plan.position << ", Normal: " << plan.normal
          << ", ReflectionType: " << plan.reflectionType
          << ", Color: " << plan.color << ")";
  return _stream;
}