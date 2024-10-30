#include "../../include/raymath/Plan.hpp"

#include <cmath>
#include <iostream>
#include <optional>
#include <vector>

Plan::Plan(Vector position, Vector normal, ReflectionType reflectionType,
           Color color, MaterialType materialType)
    : Shape(position, color, reflectionType, materialType), normal(normal) {}

Plan::Plan(Vector position, float scale, Vector normal,
           ReflectionType reflectionType, Color color,
           MaterialType materialType)
    : Shape(position, scale, color, reflectionType, materialType),
      normal(normal) {}

bool Plan::isVisible(Ray ray, Vector cameraShapeDirection) const {
  return true;
}

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
      cameraPlanDirection.computeScalable(normal);

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
  _stream << "Shape: " << static_cast<Shape const&>(plan)
          << ", Normal: " << plan.normal;
  return _stream;
}