#include "../../include/raymath/Sphere.hpp"

#include <cmath>
#include <iostream>
#include <optional>

Sphere::Sphere(Vector position, float radius, ReflectionType reflectionType,
               Color color)
    : Shape(position), radius(radius), Material(reflectionType, color) {}

Sphere::Sphere(Vector position, float scale, float radius,
               ReflectionType reflectionType, Color color)
    : Shape(position, scale), radius(radius), Material(reflectionType, color) {}

std::optional<Vector> Sphere::getIntersectPoint(Ray ray) const {
  // Calculate direction vector between camera origin and sphere center
  Vector cameraSphereDirection = getPosition() - ray.getOrigin();

  // Verify if sphere is visible from camera
  if (isVisible(ray, cameraSphereDirection) == false) {
    // std::cout << "Not visible" << std::endl;
    return std::nullopt;
  }

  // Calculate projection of direction vector on ray direction vector
  float scalarProductOfCameraSphereDirectionToRay =
      cameraSphereDirection.computeScalable(ray.getDirection().normalize());
  Vector cameraSphereDirectionProjection =
      ray.getDirection().normalize() *
      scalarProductOfCameraSphereDirectionToRay;

  // Calulate theoric intersect pointCalcule la position du point
  // d'intersection théorique
  Vector theoricIntersectPoint =
      ray.getOrigin() + cameraSphereDirectionProjection;

  // Calculate distance between sphere center and theoric intersect point
  Vector centerToTheoricIntersectPointDirection =
      theoricIntersectPoint - getPosition();
  float centerToTheoricIntersectPointLength =
      centerToTheoricIntersectPointDirection.getNorm();

  // Verify intersection
  if (isIntersect(centerToTheoricIntersectPointLength) == false) {
    // std::cout << "Not intersect" << std::endl;
    return std::nullopt;
  }

  // Calculate distance between real intersect point and theoric intesct point
  float theoricIntersectPointToRealIntersectPointLentgh =
      std::sqrt((radius * radius) - (centerToTheoricIntersectPointLength *
                                     centerToTheoricIntersectPointLength));

  // Calculate real intersect point position
  Vector theoricIntersectPointToRealIntersectPointDirection =
      ray.getDirection().normalize() *
      (-1 * theoricIntersectPointToRealIntersectPointLentgh);

  Vector realIntersectPoint =
      theoricIntersectPoint +
      theoricIntersectPointToRealIntersectPointDirection;

  return realIntersectPoint;

  // return Vector(0, 0, 0);
}

bool Sphere::isVisible(Ray ray, Vector cameraSphereDirection) const {
  // Calculate length of the direction vector
  float cameraSphereDirectionNorm = cameraSphereDirection.getNorm();
  // Normalise direction vector
  // ! Verifier normalize
  Vector cameraSphereDirectionNormalized = cameraSphereDirection.normalize();
  // Calculate scalar product between normalised direction vector and
  // normalised ray vector
  float scalarProduct = cameraSphereDirectionNormalized.computeScalable(
      ray.getDirection().normalize());

  // std::cout << "Norme" << cameraSphereDirectionNorm << "Direction nomalisé"
  //           << cameraSphereDirection << "Produit scalaire" << scalarProduct
  //           << std::endl;
  // If scalar product is greater than 0, sphere is visible
  if (scalarProduct > 0) {
    return true;
  }
  return false;
}

bool Sphere::isIntersect(float centerToTheoricIntersectPointLength) const {
  // std::cout << "Distance CP" << centerToTheoricIntersectPointLength <<
  // "Rayon"
  //           << radius << std::endl;
  if (centerToTheoricIntersectPointLength < radius) {
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere) {
  _stream << "Shape: " << static_cast<Shape const&>(sphere)
          << ", Radius: " << sphere.radius
          << ", Material: " << static_cast<Material const&>(sphere);
  return _stream;
}