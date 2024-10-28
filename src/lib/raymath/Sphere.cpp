#include "../../include/raymath/Sphere.hpp"

Sphere::Sphere(Vector position, float radius, ReflectionType reflectionType,
               Color color)
    : Shape(position), radius(radius), Material(reflectionType, color) {}

Sphere::Sphere(Vector position, float scale, float radius,
               ReflectionType reflectionType, Color color)
    : Shape(position, scale), radius(radius), Material(reflectionType, color) {}

Vector Sphere::intersect(Vector const& ray) const {
  // Implémentation spécifique pour Sphere
  return Vector();  // Remplacez par une implémentation réelle
}

std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere) {
  _stream << static_cast<Shape const&>(
                 sphere)  // Appelle l'opérateur << de Shape
          << ", Radius: " << sphere.radius << ", ReflectionType: "
          << static_cast<int>(sphere.getReflectionType())
          << ", Color: " << sphere.getColor();
  return _stream;
}