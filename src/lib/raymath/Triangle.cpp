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
  Vector edge1 = b - a;
  Vector edge2 = c - a;
  Vector normal = edge1.cross(edge2).normalize();

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

  // // L'équation de la droite : P(t) = A + t(B - A)
  // Vector d = ray.getDirection();

  // double dDotN = d.computeScalable(normal);
  // if (fabs(dDotN) < 1e-6) {  // Vérifie si la droite est parallèle au plan
  //   return std::nullopt;
  //   ;  // Pas d'intersection
  // }

  // // Calcul du paramètre t
  // float t = (normal.computeScalable(a - ray.getOrigin())) / dDotN;
  // if (t < 0) {
  //   return std::nullopt;
  //   ;  // L'intersection est derrière le point A
  // }

  // // Calcul du point d'intersection
  // Vector intersection = {ray.getOrigin().getX() + t * d.getX(),
  //                        ray.getOrigin().getY() + t * d.getY(),
  //                        ray.getOrigin().getZ() + t * d.getZ()};

  // Vérifie si le point d'intersection est à l'intérieur du triangle

  if (!isIntersect(realIntersectPoint, a, b, c)) {
    return std::nullopt;
  };

  // Retourner le point d'intersection réel
  return IntersectionResult{realIntersectPoint, normal};
}

// ! A implémenter dans la méthode getIntersectResult
bool Triangle::isVisible(Ray ray, Vector cameraTriangleDirection) const {
  // Basic visibility check, e.g., could return true if the triangle's normal
  // faces the camera or based on other visibility logic
  return true;
}

bool Triangle::isIntersect(Vector intersection, Vector a, Vector b,
                           Vector c) const {
  // Calcul des vecteurs des côtés du triangle :
  Vector edge1 = b - a;
  Vector edge2 = c - a;
  Vector edge3 = intersection - a;

  // Calcul des produits vectoriels pour chaque côté :
  float scalarProduct11 = edge1.computeScalable(edge1);
  float scalarProduct12 = edge1.computeScalable(edge2);
  float scalarProduct22 = edge2.computeScalable(edge2);
  float scalarProduct31 = edge3.computeScalable(edge1);
  float scalarProduct32 = edge3.computeScalable(edge2);

  // Déterminer les coordoné barycentrique
  float denom =
      scalarProduct11 * scalarProduct22 - scalarProduct12 * scalarProduct12;
  float barycenterX =
      (scalarProduct22 * scalarProduct31 - scalarProduct12 * scalarProduct32) /
      denom;
  float barycenterY =
      (scalarProduct11 * scalarProduct32 - scalarProduct12 * scalarProduct31) /
      denom;

  return (barycenterX >= 0) && (barycenterY >= 0) &&
         (barycenterX + barycenterY <= 1);
}

std::ostream& operator<<(std::ostream& _stream, Triangle const& triangle) {
  _stream << "Triangle: " << triangle.a << " " << triangle.b << " "
          << triangle.c << " " << triangle.getPosition() << " "
          << triangle.getColor();
  return _stream;
}
