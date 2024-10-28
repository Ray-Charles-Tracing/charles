#include "Sphere.hpp"

Sphere::Sphere(Vector position, float scale, float radius)
    : Shape(position, scale), radius(radius) {}

Vector Sphere::intersect(Vector ray) const {
  // Implémentation spécifique pour Sphere
  return Vector();  // Remplacez par une implémentation réelle
}

std::ostream& operator<<(std::ostream& _stream, Sphere const& sphere) {
  _stream << "Position: " << sphere.position << ", Scale: " << sphere.scale
          << ", Radius: " << sphere.radius;
  return _stream;
}