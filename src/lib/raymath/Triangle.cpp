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
  const double EPSILON = 1e-4;
  Vector edge1 = b - a;
  Vector edge2 = c - a;
  Vector h = ray.getDirection().cross(edge2);
  double scalableProduct = edge1.computeScalable(h);

  if (scalableProduct > -EPSILON && scalableProduct < EPSILON) {
    return std::nullopt;  // Le rayon est parallèle au triangle
  }

  double f = 1.0 / scalableProduct;
  Vector s = ray.getOrigin() - a;
  double u = f * s.computeScalable(h);

  if (u < 0.0 || u > 1.0) {
    return std::nullopt;
  }

  Vector q = s.cross(edge1);
  double v = f * ray.getDirection().computeScalable(q);

  if (v < 0.0 || u + v > 1.0) {
    return std::nullopt;
  }

  double t = f * edge2.computeScalable(q);

  if (t > EPSILON) {  // Intersection avec le triangle
    Vector intersectPoint = ray.getOrigin() + ray.getDirection() * t;
    Vector normal = edge1.cross(edge2).normalize();
    return IntersectionResult{intersectPoint, normal};
  } else {
    return std::nullopt;  // Il y a une ligne d'intersection mais pas un rayon
  }
}

// ! A implémenter dans la méthode getIntersectResult
bool Triangle::isVisible(Ray ray, Vector cameraShapeDirection) const {
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
