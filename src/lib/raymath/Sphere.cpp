#include "Sphere.hpp"

Sphere::Sphere(Vector position, float radius, ReflectionType reflectionType,
               Color color)
    : Shape(position), radius(radius), Material(reflectionType, color) {}

Sphere::Sphere(Vector position, float scale, float radius,
               ReflectionType reflectionType, Color color)
    : Shape(position, scale), radius(radius), Material(reflectionType, color) {}

Vector Sphere::intersect(Vector ray) const {
  // Implémentation spécifique pour Sphere
  return Vector();  // Remplacez par une implémentation réelle
}

std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere) {
  _stream << "Shape: " << static_cast<Shape const&>(sphere)
          << ", Radius: " << sphere.radius
          << "Material: " << static_cast<Material const&>(sphere);
  return _stream;
}